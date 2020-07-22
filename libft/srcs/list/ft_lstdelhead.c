#include "libft.h"

void	ft_lstdelhead(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*item;

	item = (*alst)->next;
	ft_lstdelone(alst, del);
	*alst = item;
}
