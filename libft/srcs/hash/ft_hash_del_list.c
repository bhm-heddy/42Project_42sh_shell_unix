#include "libft.h"

void		ft_hash_del_list(t_list **lst, void (*del)(void *))
{
	t_hash_node	*node;

	if ((node = (t_hash_node *)(*lst)->data))
	{
		ft_strdel(&node->key);
		if (del)
			del(node->data);
		free(node);
	}
	free(*lst);
}
