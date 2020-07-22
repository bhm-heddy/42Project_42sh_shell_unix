#include "libft.h"

int		str_is_digit(char *ope)
{
	while (*ope)
		if (!ft_isdigit(*ope++))
			return (0);
	return (1);
}
