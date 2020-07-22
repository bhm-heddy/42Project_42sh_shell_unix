#include "libft.h"
#include "analyzer.h"

void		**args_to_tab(t_list *lst, char *cmd)
{
	void	**tab;
	t_list	*index;
	int		i;

	index = lst;
	i = 1;
	while ((index = index->next))
		i++;
	if (!(tab = ft_memalloc(sizeof(void *) * (i + 2))))
		exit(EXIT_FAILURE);
	index = lst;
	i = 1;
	tab[0] = cmd;
	while (index)
	{
		tab[i] = index->data;
		index = index->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
