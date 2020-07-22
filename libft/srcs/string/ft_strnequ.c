#include <string.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	while (n && (*s1 == *s2) && *s1 && *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (*s1 != *s2 && (int)n > 0)
		return (0);
	else
		return (1);
}
