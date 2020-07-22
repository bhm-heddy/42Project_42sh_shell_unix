#include <unistd.h>
#include "line_edition.h"
#include "libft.h"
#include "struct.h"

int			my_putchar(int c)
{
	ft_putchar_fd((char)c, ttyslot());
	return (1);
}

char		**split_pos(const char *s)
{
	int		i;
	char	**ret;

	i = 0;
	while (*(s + i) && (*(s + i) == 27 || *(s + i) == '['))
		i++;
	ret = ft_strsplit((s + i), ";");
	return (ret);
}

void		ft_utoa(char **str)
{
	char	*s;
	int		i;

	if (str && (s = *str))
	{
		i = 0;
		while (s[i])
		{
			if ((unsigned char)s[i] > 127)
				s[i] = '@';
			i++;
		}
	}
}

void		putchar_n(char c, int n)
{
	t_cs_line	*cs;

	cs = cs_master(NULL, 0);
	while (n-- > 0)
		write(cs->tty, &c, 1);
}
