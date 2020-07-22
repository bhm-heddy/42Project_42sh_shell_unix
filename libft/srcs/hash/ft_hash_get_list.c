#include "libft.h"

t_list		*ft_hash_get_list(t_hash_map *map, char *key)
{
	uint32_t	hash;
	t_list		*lst;
	t_hash_node	*node;

	if (!(hash = ft_hash_str(map, key)))
		return (NULL);
	lst = map->slots[hash];
	while (lst)
	{
		if ((node = lst->data) && ft_strequ(node->key, key))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
