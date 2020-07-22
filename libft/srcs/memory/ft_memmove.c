#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d2;
	const char	*s2;

	d2 = dst;
	s2 = src;
	if (src < dst)
	{
		while (len--)
			d2[len] = s2[len];
	}
	else
		while (len--)
			*d2++ = *s2++;
	return (dst);
}
