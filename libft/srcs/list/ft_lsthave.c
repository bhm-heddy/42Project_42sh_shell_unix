#include "libft.h"

int			ft_lsthave(t_list *lst, int (*f)(t_list *elem))
{
	int		nb;

	nb = 0;
	while (lst)
	{
		nb += f(lst);
		lst = lst->next;
	}
	return (nb);
}
