#include "libft.h"
#include "exec.h"
#include "ft_printf.h"
#include "var.h"
#include "sh.h"

void		setvar_update(t_list *lst, char *value)
{
	if (!lst || !lst->data)
		return ;
	ft_strdel(&(((t_var *)(lst->data))->ctab[1]));
	if (!(((t_var *)(lst->data))->ctab[1] = ft_strdup(value)))
		ft_ex(EXMALLOC);
}

void		setvar_add(t_list **lst, char *var, char *value)
{
	t_var	new;

	if (!(new.ctab = (char **)malloc(sizeof(char *) * 3)))
		ft_ex(EXMALLOC);
	new.ctab[0] = ft_strdup(var);
	new.ctab[1] = ft_strdup(value);
	new.ctab[2] = NULL;
	ft_lst_push_back(lst, &new, sizeof(new));
}

uint8_t		var_check_name(char *name)
{
	if (*name > 47 && *name < 58)
		return (FAILURE);
	while (*name)
	{
		if (*name != '_' && !ft_isalnum(*name))
			return (FAILURE);
		name++;
	}
	return (SUCCESS);
}

uint8_t		ft_setvar(t_list **lst, char *name, char *value)
{
	t_list	*find;
	t_var	*var;

	find = NULL;
	if (!ft_strcmp(name, "PATH"))
		ft_hash_reset(&cfg_shell()->map, free, 128);
	if ((find = find_var(*lst, name)))
	{
		var = find->data;
		setvar_update(find, value);
		return (SUCCESS);
	}
	if (var_check_name(name))
		return (FAILURE);
	setvar_add(lst, name, value);
	return (SUCCESS);
}

uint8_t		several_setvar(t_list **var, char *str)
{
	char		*value;
	char		*tmp;
	uint8_t		err;

	value = NULL;
	err = 0;
	if ((tmp = ft_strchr(str, '='))
			&& (value = tmp + 1))
		*tmp = '\0';
	if (ft_setvar(var, str, value) == FAILURE)
		err = FAILURE;
	if (tmp)
		*tmp = '=';
	return (err);
}
