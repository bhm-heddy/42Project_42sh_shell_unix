#include "libft.h"
#include <unistd.h>
#include "struct.h"
#include "exec.h"
#include "sh.h"

static int	echo_options(char **av, int *i, int *j)
{
	char	*fl;
	int		ret;
	int		flags;

	flags = 0;
	if (av)
	{
		fl = "n";
		while ((ret = ft_getopt(i, j, av, fl)) != -1)
		{
			if (ret == (int)'?')
				break ;
			else if (ret == (int)'n')
				flags |= 2;
		}
	}
	return (flags);
}

uint8_t		ft_echo(t_process *p)
{
	t_point	i;
	int		fl;
	char	**params;

	if (bad_fd(STDOUT_FILENO) == FAILURE)
		return (1);
	if (p && (params = p->av))
	{
		i = (t_point){1, 0};
		if (((fl = echo_options(params, &i.x, &i.y)) & 1))
			i.x = 0;
		while (params[i.x])
		{
			ft_putstr(params[i.x++]);
			ft_putstr(params[i.x] ? " " : NULL);
		}
		if (!(fl & 2))
			ft_putchar('\n');
		return (0);
	}
	return (1);
}
