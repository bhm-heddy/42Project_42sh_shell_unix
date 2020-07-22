#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;

	i = 0;
	while (n--)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((unsigned char *)s)[i]);
		i++;
	}
	return (NULL);
}
