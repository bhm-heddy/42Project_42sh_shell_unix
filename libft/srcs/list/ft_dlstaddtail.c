#include "libft.h"

void	ft_dlstaddtail(t_dlist **alst, t_dlist *new)
{
	t_dlist	*ptr;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	ptr = *alst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
}
