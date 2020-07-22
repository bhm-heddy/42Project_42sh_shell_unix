#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;

	if (!(s2 = ft_strnew(n)))
		return (NULL);
	return (ft_strncpy(s2, s1, n));
}
