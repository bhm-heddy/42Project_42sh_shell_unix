#include "libft.h"

uint32_t	ft_lstcount(t_list *elem)
{
	uint32_t	nb;

	nb = 0;
	while (elem && ++nb)
		elem = elem->next;
	return (nb);
}
