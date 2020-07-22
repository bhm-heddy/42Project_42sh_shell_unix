#include <stdio.h>

char	ft_checkopt(char av, char *flags)
{
	while (*flags)
	{
		if (*flags == av)
			return (av);
		flags++;
	}
	return ('?');
}

int		ft_getopt(int *ac, int *i, char **const av, char *flags)
{
	char		option;

	if (av[*ac] && (*i != 0 || (av[*ac][(*i)++] == '-')))
	{
		if (av[*ac][*i] == '-')
		{
			*ac += 1;
			return (-1);
		}
		if (((option = ft_checkopt(av[*ac][*i], flags)) == '?')
				|| av[*ac][++(*i)])
			return (option);
		*i = 0;
		*ac += 1;
		return (option);
	}
	return (-1);
}
