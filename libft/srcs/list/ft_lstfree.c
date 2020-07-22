#include "libft.h"

void		ft_lstfree(void *data, size_t size)
{
	(void)size;
	free(data);
}
