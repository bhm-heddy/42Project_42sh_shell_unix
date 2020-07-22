#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"

void		**lst_to_tab(t_list *lst)
{
	void	**tab;
	t_list	*index;
	int		i;

	if (!lst)
		return (NULL);
	index = lst;
	i = 1;
	while ((index = index->next))
		i++;
	if (!(tab = ft_memalloc(sizeof(void *) * (i + 1))))
	{
		ft_printf("erreur allocation lst_to_tab\n");
		exit(EXIT_FAILURE);
	}
	index = lst;
	i = 0;
	while (index)
	{
		tab[i] = index->data;
		index = index->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
