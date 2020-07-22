#include "libft.h"

void	ft_dlstdel(t_dlist **alst)
{
	t_dlist		*tmp;
	t_dlist		*tmp2;

	if (alst && (tmp = *alst))
	{
		while (tmp->prev)
			tmp = tmp->prev;
		while (tmp)
		{
			tmp2 = tmp->next;
			ft_memdel((void **)&tmp->data);
			ft_memdel((void **)&tmp);
			if (tmp2)
				tmp2->prev = NULL;
			tmp = tmp2;
		}
		alst = NULL;
	}
}
