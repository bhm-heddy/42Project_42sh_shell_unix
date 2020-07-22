#include "libft.h"

int	ft_strisalpha(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		if (!ft_isalpha(s[i++]))
			return (0);
	return (1);
}
