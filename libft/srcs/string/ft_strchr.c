#include <stdlib.h>

char	*ft_strchr(char const *s, int c)
{
	int	i;

	if (s)
	{
		i = 0;
		while (s[i] != (char)c && s[i] != '\0')
			i++;
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	}
	return (NULL);
}
