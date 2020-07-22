#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char *s2;

	s2 = s;
	while (n--)
		*s2++ = '\0';
}
