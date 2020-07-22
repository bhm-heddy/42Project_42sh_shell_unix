#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t size))
{
	if (!(*alst))
		return ;
	if ((*alst)->next)
		ft_lstdel(&(*alst)->next, del);
	ft_lstdelone(alst, del);
}
