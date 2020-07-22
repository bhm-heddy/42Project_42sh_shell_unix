#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d2;
	unsigned char		*s2;
	unsigned char		c2;
	int					i;

	i = 0;
	s2 = (unsigned char *)src;
	d2 = dst;
	c2 = c;
	while (n--)
	{
		d2[i] = s2[i];
		if (s2[i] == c2)
			return (&d2[i + 1]);
		i++;
	}
	return (NULL);
}
