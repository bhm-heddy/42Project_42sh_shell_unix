#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	i = -1;
	if (!s1)
		return (NULL);
	if (!(dest = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		exit(EXIT_FAILURE);
	while (s1[++i])
		dest[i] = s1[i];
	dest[i] = '\0';
	return (dest);
}
