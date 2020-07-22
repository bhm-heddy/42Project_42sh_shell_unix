#include "libft.h"

void		*ft_hash_lookup(t_hash_map *map, char *key)
{
	t_hash_node	*node;

	if (!(node = ft_hash_get_node(map, key)))
		return (NULL);
	return (node->data);
}
