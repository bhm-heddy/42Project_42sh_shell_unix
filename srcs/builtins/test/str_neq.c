#include "libft.h"

uint8_t		test_diff_string(char *s1, char *s2)
{
	return ((ft_strequ(s1, s2) == 0) ? 0 : 1);
}
