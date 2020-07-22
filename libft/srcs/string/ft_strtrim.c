#include "libft.h"

static int	endspace(const char *s)
{
	int		i;

	i = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && i > 0)
		i--;
	return (i);
}

static int	beginspace(const char *s)
{
	int		i;

	i = 0;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i])
		i++;
	return (i);
}

char		*ft_strtrim(char const *s)
{
	int		len;
	char	*dst;

	len = endspace(s) - beginspace(s) + 1;
	if (len < 0)
		len = 0;
	dst = ft_strnew(len);
	if (!dst)
		return (NULL);
	ft_strncpy(dst, &s[beginspace(s)], len);
	return (dst);
}
