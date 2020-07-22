#include "libft.h"

int		ft_strrchri(const char *s, int c)
{
	int i;

	i = ft_strlen(s) + 1;
	while (i-- != 0)
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}
