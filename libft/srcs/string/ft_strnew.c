#include "../../includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	int		i;

	i = (int)size;
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	while (i >= 0)
	{
		str[i] = '\0';
		i--;
	}
	return (str);
}
