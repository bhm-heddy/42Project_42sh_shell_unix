#include "line_edition.h"
#include "struct.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <sys/ioctl.h>
#include "sh.h"

void			print_prompt(t_cs_line *cs)
{
	int			len;
	t_cfg		*cfg;

	if (cs && (cfg = cfg_shell()) && cfg->interactive)
	{
		ft_putstr_fd(cs->prompt_color, cs->tty);
		if (cs->screen.x <= (len = (int)ft_strlen(cs->prompt)
			+ (cs->scroll ? 1 : 0)))
		{
			tputs(tgoto(tgetstr("cm", NULL), cs->min_col, cs->min_row),
				1, &my_putchar);
			len = len - cs->screen.x;
			ft_putstr_fd(&cs->prompt[len], cs->tty);
			if (cs->scroll == 0)
				ft_putstr_fd("\n", cs->tty);
		}
		else
		{
			tputs(tgoto(tgetstr("cm", NULL), cs->min_col, cs->min_row),
				1, &my_putchar);
			ft_putstr_fd(cs->prompt, cs->tty);
		}
		ft_putstr_fd("\e[0;0m", cs->tty);
	}
}

void			cmdline_printer(t_cs_line *cs, t_point start, t_point end)
{
	char	oc;

	if (cs)
	{
		oc = cs->input[start.y];
		cs->input[start.y] = '\0';
		ft_putstr_fd(&cs->input[start.x], cs->tty);
		cs->input[start.y] = oc;
		if (cs->clipb.x != -1 && cs->clipb.y != -1
			&& cs->clipb.x != cs->clipb.y)
			tputs(tgetstr("mr", NULL), 1, &my_putchar);
		oc = cs->input[end.y];
		cs->input[end.y] = '\0';
		ft_putstr_fd(&cs->input[start.y], cs->tty);
		cs->input[end.y] = oc;
		if (cs->clipb.x != -1 && cs->clipb.y != -1
			&& cs->clipb.x != cs->clipb.y)
			tputs(tgetstr("me", NULL), 1, &my_putchar);
		oc = cs->input[end.x];
		cs->input[end.x] = '\0';
		ft_putstr_fd(&cs->input[end.y], cs->tty);
		cs->input[end.x] = oc;
	}
}

void			print_cmdline(t_cs_line *cs)
{
	t_point		z;
	t_point		start;
	t_point		end;

	ft_clear(1);
	if (cs && cs->input && cs->line_col >= 0)
	{
		print_prompt(cs);
		z = trim_input(cs);
		start.x = z.x;
		end.x = z.y;
		if (end.x < (int)ft_strlen(cs->input))
			end.x++;
		start.y = (cs->clipb.x >= start.x && cs->clipb.x <= end.x)
			? cs->clipb.x : start.x;
		end.y = (cs->clipb.y >= start.x && cs->clipb.y <= end.x)
			? cs->clipb.y : end.x;
		cmdline_printer(cs, start, end);
		move_cs(&cs);
	}
}

static void		clear_line(t_point *col, struct winsize ws, t_cs_line *cs,
int dl_p)
{
	if (col->y++ == cs->min_row)
	{
		if (dl_p == 1)
			tputs(tgetstr("ce", NULL), 1, &my_putchar);
		tputs(tgoto(tgetstr("cm", NULL), 0, cs->min_row + 1), 1, &my_putchar);
	}
	else if (col->y - 1 != cs->min_row && col->y - 1 < ws.ws_row)
		tputs(tgetstr("dl", NULL), ws.ws_col, &my_putchar);
}

void			ft_clear(int del_prompt)
{
	t_point			col;
	t_cs_line		*cs;
	struct winsize	ws;
	int				col_prompt;

	if ((cs = cs_master(NULL, 0)))
	{
		col.x = cs->min_col;
		col.y = cs->min_row;
		ioctl(cs->tty, TIOCGWINSZ, &ws);
		col_prompt = (int)ft_strlen(cs->prompt);
		col_prompt -= (col_prompt > cs->screen.x ? cs->screen.x : 0);
		tputs(tgoto(tgetstr("cm", NULL), cs->min_col + col_prompt, cs->min_row),
			1, &my_putchar);
		while (col.y < ws.ws_row)
			clear_line(&col, ws, cs, del_prompt);
		tputs(tgoto(tgetstr("cm", NULL), cs->min_col + col_prompt, cs->min_row),
			1, &my_putchar);
	}
}
