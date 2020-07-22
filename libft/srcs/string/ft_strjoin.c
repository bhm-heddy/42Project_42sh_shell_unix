#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2 || !(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	if (!(str = ft_strcat(str, (char *)s1))
	|| !(str = ft_strcat(str, (char *)s2)))
		return (NULL);
	return (str);
}
