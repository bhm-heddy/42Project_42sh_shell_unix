#include "exec.h"
#include "line_edition.h"
#include "libft.h"
#include <struct.h>
#include <sh.h>
#include "var.h"

int	print_hist(int8_t *fl, char **av, int ac)
{
	t_point	range;
	int		order;
	t_cfg	*cfg;
	char	*key;

	if (av && (cfg = cfg_shell()) && check_range(av, ac) == 1)
	{
		range = get_range(fl, av, ac, cfg);
		if (*fl & 8)
			range = (t_point){range.y, range.x};
		order = (range.x > range.y ? -1 : 1);
		while (range.x - order != range.y && range.x > 0)
		{
			if (!(*fl & 4))
				ft_putnbr(range.x);
			putchar_n(' ', (!(*fl & 4) ? 12 - ft_intlen(range.x) : 12));
			key = ft_itoa(range.x);
			ft_putendl((char *)ft_hash_lookup(cfg->hist_map, key));
			ft_strdel(&key);
			range.x += order;
		}
		return (1);
	}
	return (-1);
}
