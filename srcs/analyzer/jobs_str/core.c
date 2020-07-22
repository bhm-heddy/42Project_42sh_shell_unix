#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "analyzer.h"
#include "var.h"
#include "line_edition.h"
#include "sh.h"

static char		*get_assign_str(t_list *assign_lst)
{
	t_assignment	*assign;
	char			*new;
	char			*res;
	char			*tmp;

	if (!assign_lst || !assign_lst->data)
		return (NULL);
	assign = (t_assignment *)assign_lst->data;
	if (ft_asprintf(&res, "%s=%s", assign->var, assign->val) == -1)
		ft_ex(EXMALLOC);
	assign_lst = assign_lst->next;
	while (assign_lst && assign)
	{
		assign = (t_assignment *)assign_lst->data;
		if (ft_asprintf(&new, "%s=%s", assign->var, assign->val) == -1)
			ft_ex(EXMALLOC);
		if (ft_asprintf(&tmp, "%s %s", res, new) == -1)
			ft_ex(EXMALLOC);
		ft_strdel(&res);
		ft_strdel(&new);
		res = tmp;
		assign_lst = assign_lst->next;
	}
	return (res);
}

static char		*add_str_to_job(char **str, char **new)
{
	char	*res;

	res = NULL;
	if (!str || !new)
		return (NULL);
	if (!*str && *new)
	{
		if (!(res = ft_strdup(*new)))
			ft_ex(EXMALLOC);
	}
	else if (*str && *new)
	{
		if (ft_asprintf(&res, "%s %s", *str, *new) == -1)
			ft_ex(EXMALLOC);
	}
	else if (*str && !*new)
	{
		if (!(res = ft_strdup(*str)))
			ft_ex(EXMALLOC);
	}
	if (*new)
		ft_strdel(new);
	if (*str)
		ft_strdel(str);
	return (res);
}

static char		*get_cmd_str(t_simple_cmd *cmd)
{
	char	*str;
	char	*assign;
	char	*args;
	char	*redir;

	str = NULL;
	assign = get_assign_str(cmd->assign);
	str = add_str_to_job(&str, &assign);
	args = get_args_str(cmd->av);
	str = add_str_to_job(&str, &args);
	redir = get_redir_str(cmd->redir);
	str = add_str_to_job(&str, &redir);
	return (str);
}

static int		a_and_or_job_str(t_and_or *and_or)
{
	t_list	*cmd_lst;
	char	*str;
	char	*res;
	char	*tmp;

	res = NULL;
	cmd_lst = and_or->s_cmd;
	if (cmd_lst->data && !(res = get_cmd_str((t_simple_cmd *)cmd_lst->data)))
		return (1);
	cmd_lst = cmd_lst->next;
	while (cmd_lst)
	{
		if (cmd_lst->data
		&& !(str = get_cmd_str((t_simple_cmd *)cmd_lst->data)))
			return (1);
		if (cmd_lst->data && ft_asprintf(&tmp, "%s | %s", res, str) == -1)
			ft_ex(EXMALLOC);
		ft_strdel(&str);
		ft_strdel(&res);
		res = tmp;
		cmd_lst = cmd_lst->next;
	}
	and_or->str = res;
	return (1);
}

void			a_set_jobs_str(t_and_or *and_or)
{
	if (and_or)
		a_and_or_job_str(and_or);
}
