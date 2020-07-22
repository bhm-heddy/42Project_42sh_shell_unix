#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d2;
	const char	*s2;

	d2 = dst;
	s2 = src;
	while (n--)
		*d2++ = *s2++;
	return (dst);
}
