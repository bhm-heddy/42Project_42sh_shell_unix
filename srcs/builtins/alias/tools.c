#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "var.h"
#include "sh.h"
#include "exec.h"

t_var				*search_alias_var(char *name, t_list *list)
{
	t_var		*var;

	if (!list)
		return (NULL);
	while (list)
	{
		var = list->data;
		if (var && ft_strequ(name, var->ctab[0]))
			return (var);
		list = list->next;
	}
	return (NULL);
}

t_list				*search_alias_list(char *name, t_list *list)
{
	t_var		*var;

	if (!list)
		return (NULL);
	while (list)
	{
		var = list->data;
		if (var && ft_strequ(name, var->ctab[0]))
			return (list);
		list = list->next;
	}
	return (NULL);
}

char				*search_alias_value(char *name, t_list *list)
{
	t_var	*var;

	if (!(var = search_alias_var(name, list)))
		return (NULL);
	return (var->ctab[1]);
}
