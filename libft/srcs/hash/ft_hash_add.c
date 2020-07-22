#include "libft.h"

int		ft_hash_add(t_hash_map *map, char *key,
		void *value, void (*del)(void *))
{
	uint32_t	hash;
	t_list		*lst;
	t_hash_node	*node;

	if (ft_hash_get_node(map, key))
		ft_hash_delone(map, key, del);
	hash = ft_hash_str(map, key);
	lst = map->slots[hash];
	if (!(node = (t_hash_node *)ft_memalloc(sizeof(t_hash_node)))
	|| !(node->key = ft_strdup(key)))
		return (0);
	node->data = value;
	if (!(lst = ft_lstpush(&map->slots[hash], node, sizeof(t_hash_node *))))
		return (0);
	return (1);
}
