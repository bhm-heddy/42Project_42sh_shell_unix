#include <stdlib.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		r;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			r = i;
			while ((haystack[i + j] == needle[j]) && haystack[i + j]
					&& needle[j])
				j++;
			if (needle[j] == '\0')
				return ((char *)&haystack[r]);
		}
		i++;
	}
	return (NULL);
}
