#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if (s1 && s2)
		return (ft_strcmp((char*)s1, (char*)s2) == 0);
	return (0);
}
