#include "libft.h"

size_t		ft_wstrlen(unsigned *str)
{
	size_t	len;

	len = 0;
	while (*str != L'\0')
	{
		len += ft_wcharlen(*str);
		str++;
	}
	return (len);
}
