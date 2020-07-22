#include "libft.h"
#include "struct.h"
#include "line_edition.h"

void	home_key(t_cs_line *cs)
{
	int	cr;

	if (cs)
	{
		cs->line_col = 0;
		cr = get_line(cs);
		cs->scroll = cr - (cs->screen.y - cs->min_row - 1);
		if (cs->scroll < 0)
			cs->scroll = 0;
		print_cmdline(cs);
		move_cs(&cs);
	}
}

void	end_key(t_cs_line *cs)
{
	int	cr;

	if (cs && (cs->line_col = (int)ft_strlen(cs->input)) >= 0)
	{
		cr = get_line(cs);
		cs->scroll = cr - (cs->screen.y - cs->min_row - 1);
		if (cs->scroll < 0)
			cs->scroll = 0;
		print_cmdline(cs);
		move_cs(&cs);
		if (cs->sig_int)
			ft_putstr_fd("^C\n", cs->tty);
		if (cs->sig_eof)
			ft_putstr_fd("\n", cs->tty);
	}
}

int		ctrl_d(t_cs_line *cs)
{
	if (cs)
	{
		if (ft_strlen(cs->input) > 0)
			return (revback_space(cs));
		else
		{
			ft_strdel(&cs->input);
			if (cs->history)
				cs->history->data = NULL;
			cs->sig_eof = 1;
		}
	}
	return (-1);
}
