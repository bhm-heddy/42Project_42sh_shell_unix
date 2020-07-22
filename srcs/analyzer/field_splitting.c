#include "analyzer.h"
#include "debug.h"
#include "sh.h"
#include "var.h"
#include "libft.h"

static void		process_quotes(int *quote, int *bs, char *str)
{
	if (*str == '\'' && *quote < 2)
		*quote = *quote == 1 ? 0 : 1;
	else if (*str == '\"' && *quote != 1)
		*quote = *quote == 2 ? 0 : 2;
	else if (*str == '\\' && *quote != 1)
		*bs = 2;
}

static int		word_len(char *str, char *set)
{
	int		ret;
	int		quote;
	int		bs;

	quote = 0;
	bs = 0;
	ret = 0;
	while (*str && (quote || bs || !ft_strchr(set, *str)))
	{
		if (!bs && ft_strchr("\'\"\\", *str))
			process_quotes(&quote, &bs, str);
		if (bs)
			bs--;
		ret++;
		str++;
	}
	return (ret);
}

static void		split_fields(char *str, char *set, t_list **lst)
{
	int		wlen;

	while (*str)
	{
		if (!ft_strchr(set, *str))
		{
			wlen = word_len(str, set);
			if (!ft_lstpush(lst, ft_strndup(str, wlen), sizeof(char *))
			|| !(*lst)->data)
				ft_ex(EXMALLOC);
			str += wlen;
		}
		if (*str)
			str++;
	}
}

static void		cmd_replace(t_simple_cmd *cmd, t_list *res)
{
	ft_strdel(&cmd->cmd_name);
	ft_lstdel(&cmd->args, ft_lstfree);
	if (res)
	{
		cmd->cmd_name = res->data;
		cmd->args = res->next;
		free(res);
	}
}

void			field_splitting(t_simple_cmd *cmd)
{
	char		*ifs;
	t_list		*res;
	t_list		*lst;

	res = NULL;
	if ((cfg_shell()->debug))
		field_splitting_debug(cmd, "START");
	if ((ifs = find_var_value(cfg_shell()->env, "IFS"))
	&& (!(ifs = ft_strdup(ifs))))
		ft_ex(EXMALLOC);
	if (!ifs && !(ifs = ft_strdup(" \t\n")))
		ft_ex(EXMALLOC);
	if (cmd->cmd_name)
		split_fields(cmd->cmd_name, ifs, &res);
	lst = cmd->args;
	while (lst)
	{
		split_fields(lst->data, ifs, &res);
		lst = lst->next;
	}
	free(ifs);
	cmd_replace(cmd, res);
	if ((cfg_shell()->debug))
		field_splitting_debug(cmd, "END");
}
