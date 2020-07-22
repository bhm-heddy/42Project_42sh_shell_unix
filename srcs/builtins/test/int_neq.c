#include "libft.h"
#include "exec.h"

uint8_t		test_diff_int(char *s1, char *s2)
{
	if (!check_int_args(s1, s1))
		return (2);
	return ((ft_atoi(s1) != ft_atoi(s2)) ? 0 : 1);
}
