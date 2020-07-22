#include "libft.h"

t_list	*ft_lstgettail(t_list *alst)
{
	if (!alst)
		return (NULL);
	while (alst->next)
		alst = alst->next;
	return (alst);
}
