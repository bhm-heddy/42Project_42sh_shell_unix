#include "libft.h"

int	ft_strisdigit(char *s)
{
	int	i;

	i = 0;
	while (s && s[i++])
		if (!ft_isdigit(s[i - 1]) && s[i - 1] != '+' && s[i - 1] != '-')
			return (0);
	return (1);
}
