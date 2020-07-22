#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *b2;

	b2 = b;
	while (len--)
		*b2++ = c;
	return (b);
}
