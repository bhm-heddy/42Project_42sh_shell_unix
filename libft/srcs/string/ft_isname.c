#include "../../includes/libft.h"

int	ft_isname(char *str)
{
	if (ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isalnum((int)*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
