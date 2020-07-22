#include "libft.h"

void	ft_hash_reset(t_hash_map **map, void (*del)(void *data), uint32_t size)
{
	ft_hash_del_map(map, del);
	*map = ft_hash_init(size);
}
