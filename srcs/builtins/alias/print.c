#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "var.h"
#include "sh.h"
#include "exec.h"

static void	fill_quoted_string(char *src, char *res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\'')
		{
			ft_strcpy(res + j, "\'\\\'\'");
			j += 4;
		}
		else
		{
			res[j] = src[i];
			j++;
		}
		i++;
	}
}

void		print_alias(t_var *var)
{
	char	*quoted;
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	if (!var)
		return ;
	while (var->ctab[1][i])
		if (var->ctab[1][i++] == '\'')
			cnt++;
	if (!(quoted = ft_strnew(ft_strlen(var->ctab[1]) + (cnt * 4))))
		ft_ex(EXMALLOC);
	fill_quoted_string(var->ctab[1], quoted);
	ft_printf("%s=\'%s\'\n", var->ctab[0], quoted);
	ft_strdel(&quoted);
}

int			print_single_alias(char *name)
{
	t_var	*var;

	if ((var = search_alias_var(name, cfg_shell()->alias)))
	{
		print_alias(var);
		return (0);
	}
	ft_dprintf(2, "%s: alias: %s : Not found\n", PROJECT, name);
	return (1);
}

void		print_all_alias(void)
{
	t_list	*list;

	list = cfg_shell()->alias;
	while (list)
	{
		print_alias(list->data);
		list = list->next;
	}
}
