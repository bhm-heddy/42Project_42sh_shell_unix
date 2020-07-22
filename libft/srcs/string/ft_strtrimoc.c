#include "libft.h"

static int	endspace(const char *s, char oc)
{
	int		i;

	i = ft_strlen(s) - 1;
	while (i > 0 && s[i] == oc)
		i--;
	return (i);
}

static int	beginspace(const char *s, char oc)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == oc)
		i++;
	return (i);
}

char		*ft_strtrimoc(char const *s, char oc)
{
	int		len;
	char	*dst;

	len = endspace(s, oc) - beginspace(s, oc) + 1;
	if (len < 0)
		len = 0;
	dst = ft_strnew(len);
	if (!dst)
		return (NULL);
	ft_strncpy(dst, &s[beginspace(s, oc)], len);
	return (dst);
}
