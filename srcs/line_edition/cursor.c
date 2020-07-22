#include "libft.h"
#include "line_edition.h"
#include "struct.h"

void		cs_set(void)
{
	struct winsize	size;
	t_cs_line		*cs;

	if ((cs = cs_master(NULL, 0)))
	{
		ioctl(cs->tty, TIOCGWINSZ, &size);
		cs->screen.x = size.ws_col;
		cs->screen.y = size.ws_row;
		cs->tty = ttyslot();
	}
}

void		move_cs(t_cs_line **cs)
{
	t_cs_line	*tmp;
	t_point		pos;

	if (cs && (tmp = *cs) && tmp->input && tmp->input[0])
	{
		pos = cs_pos(tmp);
		tmp->col = pos.x;
		tmp->row = pos.y;
		tputs(tgoto(tgetstr("cm", NULL), tmp->col, tmp->row), 1, &my_putchar);
	}
}

t_cs_line	*cs_master(char *prompt, int init)
{
	static t_cs_line cs;

	if (init == 1)
	{
		ft_bzero(&cs, 20);
		cs.history = NULL;
		get_cs_line_position(&cs.min_col, &cs.min_row);
		cs.col = 0;
		cs.row = cs.min_row;
		cs.scroll = 0;
		cs.line_col = 0;
		cs.max_scroll = 0;
		cs.input = ft_strnew(0);
		cs.prompt = prompt;
		cs.clipb.x = -1;
		cs.clipb.y = -1;
		cs.sig_int = 0;
		cs.sig_eof = 0;
		cs.old_history = NULL;
	}
	return (&cs);
}
