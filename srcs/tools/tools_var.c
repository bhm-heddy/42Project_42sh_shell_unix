#include "libft.h"
#include "exec.h"
#include "sh.h"
#include "ft_printf.h"

void		cpy_var_list(void *dst, void *src)
{
	t_var *d;
	t_var *s;

	d = dst;
	s = src;
	d->ctab = ft_tabdup(s->ctab);
}

t_list		*find_var(t_list *lst, char *name)
{
	t_var *var;

	while (lst)
	{
		var = lst->data;
		if (!ft_strcmp(var->ctab[0], name))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char		*find_var_value(t_list *var, char *name)
{
	t_list	*lst;

	lst = find_var(var, name);
	if (lst)
		return (((t_var *)(lst->data))->ctab[1]);
	return (NULL);
}
