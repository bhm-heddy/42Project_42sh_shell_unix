#include "exec.h"
#include "line_edition.h"
#include "libft.h"
#include <struct.h>
#include <sh.h>
#include "ft_printf.h"
#include "get_next_line.h"
#include "var.h"

uint8_t	fc_check_opt(t_process *p, int32_t *ac)
{
	int32_t	i;
	int		z;
	int8_t	ret;
	int8_t	flags;

	i = 0;
	flags = 0;
	while ((ret = ft_getopt(ac, &i, p->av, "elnrs")) != -1)
	{
		if (ret == '?' && (z = i) >= 0)
		{
			while (p->av[*ac][z])
				if (!ft_isdigit(p->av[*ac][z++]))
					return (fc_bad_option(&p->av[*ac][i]));
			break ;
		}
		flags |= (char)ret == 'e' ? 1 : 0;
		flags |= (char)ret == 'l' ? 2 : 0;
		flags |= (char)ret == 'n' ? 4 : 0;
		flags |= (char)ret == 'r' ? 8 : 0;
		flags |= (char)ret == 's' ? 16 : 0;
		if ((flags & 1 && flags & 2))
			return (fc_bad_usage((!p->av[*ac] ? p->av[*ac - 1] : p->av[*ac])));
	}
	return (flags);
}

t_point	get_range(int8_t *fl, char **av, int ac, t_cfg *cfg)
{
	t_point t;

	if (av && av[ac])
	{
		if (!av[ac + 1] || (t.y = ft_atoi(av[ac + 1])) == 0
			|| t.y > cfg->hist_nb)
			t.y = cfg->hist_nb - 1;
		if (t.y < 0)
			t.y = cfg->hist_nb + t.y;
		if ((t.x = ft_atoi(av[ac])) == 0 || t.x > cfg->hist_nb)
			t.x = cfg->hist_nb - 1;
		if (t.x < 0)
			t.x = cfg->hist_nb + t.x;
		if (t.x > t.y)
		{
			t = (t_point){t.y, t.x};
			*fl = (*fl & 8 ? *fl ^ 8 : *fl | 8);
		}
	}
	else
	{
		t.y = cfg->hist_nb - 1;
		t.x = (cfg->hist_nb <= 15 ? 1 : cfg->hist_nb - 15);
	}
	return (t);
}

int		check_range(char **av, int ac)
{
	int i;
	int z;

	if (av && av[ac])
	{
		i = ac;
		while (av[i])
		{
			z = 0;
			if (ft_strcmp(av[i], "-") == 0)
				return (range_error());
			if (av[i][z] == '-')
				z = 1;
			while (av[i][z])
				if (!ft_isdigit(av[i][z++]))
					return (range_error());
			i++;
		}
	}
	return (1);
}

int		ft_intlen(int nb)
{
	unsigned int	n;
	int				ret;

	if (nb < 0)
		n = nb * (-1);
	else
		n = (unsigned int)nb;
	if (n == 0)
		return (1);
	ret = 0;
	while (n && ret++ >= 0)
		n /= 10;
	return (ret);
}
