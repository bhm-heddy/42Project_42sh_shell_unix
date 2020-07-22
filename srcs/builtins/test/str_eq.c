#include "libft.h"

uint8_t		test_equal_string(char *s1, char *s2)
{
	return ((ft_strequ(s1, s2) == 0) ? 1 : 0);
}
