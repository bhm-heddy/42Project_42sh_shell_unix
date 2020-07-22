#include <stdlib.h>

static int		ft_len(long len)
{
	int		i;

	i = 0;
	while (len > 0)
	{
		len = len / 10;
		i++;
	}
	return (i);
}

static char		*ft_itoaposi(long n)
{
	long	len;
	char	*src;

	len = ft_len(n);
	src = (char *)malloc(sizeof(char) * len + 1);
	if (!src)
		return (NULL);
	src[len] = '\0';
	while (--len >= 0)
	{
		src[len] = 48 + (n % 10);
		n = n / 10;
	}
	return (src);
}

static char		*ft_itoanega(long n)
{
	char	*src;
	long	len;

	n = n * -1;
	len = ft_len(n);
	src = (char *)malloc(sizeof(char) * len + 2);
	if (!src)
		return (NULL);
	src[len + 1] = '\0';
	src[0] = 45;
	while (0 < len)
	{
		src[len] = 48 + (n % 10);
		n = n / 10;
		len--;
	}
	return (src);
}

char			*ft_itoa(int n)
{
	char	*src;
	long	nb;

	nb = n;
	if (nb > 0)
		return (ft_itoaposi(nb));
	if (nb < 0)
		return (ft_itoanega(nb));
	else
	{
		src = (char *)malloc(sizeof(char) * 2);
		if (!src)
			return (NULL);
		src[0] = 48;
		src[1] = '\0';
		return (src);
	}
}
