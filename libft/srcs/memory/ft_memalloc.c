#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*s;

	if (!(s = malloc(size)))
		return (NULL);
	return (ft_memset(s, 0, size));
}
