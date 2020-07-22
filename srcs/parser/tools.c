#include "libft.h"
#include "lexer.h"
#include "parser.h"

int	is_digitstr(char *str)
{
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}
