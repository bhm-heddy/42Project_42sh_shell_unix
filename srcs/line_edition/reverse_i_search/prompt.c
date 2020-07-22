#include "libft.h"
#include "line_edition.h"
#include "struct.h"
#include "ft_printf.h"
#include "sh.h"

char	*set_prompt(char *s)
{
	static char	*prompt = NULL;

	if (s)
		prompt = s;
	return (prompt);
}

int		rev_i_search(t_cs_line *cs)
{
	if (cs && cs->ctrl_r == 0)
	{
		set_prompt(cs->prompt);
		cs->prompt = ft_strdup("(reverse-i-search)> ");
		cs->ctrl_r = 1;
		ft_clear(1);
		print_prompt(cs);
	}
	return (0);
}

int		ctrl_r_off(t_cs_line *cs, char *caps)
{
	(void)caps;
	if (cs && cs->ctrl_r == 1)
	{
		ft_strdel(&cs->prompt);
		cs->prompt = set_prompt(NULL);
		cs->ctrl_r = 0;
		if (caps[0] == (char)4)
			print_cmdline(cs);
	}
	return (0);
}

int		del_char(char **del, t_dlist *hist, t_cs_line *cs)
{
	int		i;
	char	*tmp;

	if (del && *del && (i = ft_strlen(*del)))
	{
		ft_putnbr(i);
		tmp = *del;
		tmp[i - 1] = '\0';
		*del = ft_strdup(tmp);
		ft_strdel(&tmp);
		ft_clear(1);
		print_prompt(cs);
		ft_dprintf(cs->tty, "\"%s\" : %s", *del,
				(hist ? (char *)hist->data : NULL));
		return (1);
	}
	return (0);
}
