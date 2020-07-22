#include "libft.h"
#include "exec.h"
#include "sh.h"
#include "ft_printf.h"

uint8_t		ft_print_var_lst(t_list *lst, uint8_t i)
{
	t_var	*env;
	char	*export;

	export = (i > 0) ? "export " : "";
	while (lst)
	{
		env = lst->data;
		ft_printf("%s%s=%s\n", export, env->ctab[0], env->ctab[1]);
		lst = lst->next;
	}
	return (SUCCESS);
}

char		**create_tab_var(t_list *lst, int count)
{
	char	**tab;
	t_var	*var;

	if (!lst)
		return (NULL);
	if (lst->next)
		tab = create_tab_var(lst->next, ++count);
	if (!lst->next)
	{
		count++;
		if (!(tab = (char **)malloc(sizeof(char *) * (count + 1))))
			ft_ex(EXMALLOC);
		tab[count] = NULL;
	}
	count--;
	var = lst->data;
	ft_asprintf(&tab[count], "%s=%s", var->ctab[0], var->ctab[1]);
	return (tab);
}

char		**create_var_tab(char *s)
{
	char	*tmp;
	char	**tab;

	tab = ft_memalloc(sizeof(char *) * 3);
	protect_malloc(tab);
	if ((tmp = ft_strchr(s, '=')))
	{
		*tmp = '\0';
		tmp += 1;
		tab[1] = ft_strdup(tmp);
	}
	else
		tab[1] = ft_memalloc(sizeof(char));
	tab[0] = ft_strdup(s);
	protect_malloc(tab[0]);
	protect_malloc(tab[1]);
	return (tab);
}

void		create_lst_var(t_list **lst, char **tab)
{
	int		i;
	t_var	var;

	i = 0;
	*lst = NULL;
	if (!tab || !*tab)
		return ;
	while (tab[i])
	{
		var.ctab = create_var_tab(tab[i]);
		ft_lst_push_back(lst, &var, sizeof(t_var));
		i++;
	}
}
