#include "../../includes/libft.h"

void	ft_print_bits(unsigned char nb)
{
	int	i;
	int	c;

	i = 128;
	c = 0;
	while (nb > 0)
	{
		if (nb / i > 0)
		{
			ft_putchar('1');
			nb = nb - i;
			c++;
		}
		else
		{
			ft_putchar('0');
			c++;
		}
		i = i / 2;
	}
	while (c < 8)
	{
		ft_putchar('0');
		c++;
	}
}
