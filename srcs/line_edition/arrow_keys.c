#include "line_edition.h"
#include "struct.h"
#include "libft.h"

void	arrow_up(t_cs_line *cs)
{
	if (cs)
	{
		if (cs->line_col > cs->screen.x)
			cs->line_col -= cs->screen.x;
		else if (cs->line_col > cs->screen.x - cs->min_col)
			cs->line_col -= cs->screen.x - cs->min_col;
		cs->cr = get_line(cs);
		if (cs->cr + cs->min_row - cs->scroll - 1 <= cs->min_row && cs->scroll)
		{
			cs->scroll = cs->cr - (cs->screen.y - cs->min_row + (cs->screen.x
						> 2 ? 0 : 1) + (cs->scroll > 0 ? 1 : 0) - 1);
			print_cmdline(cs);
		}
		if (cs->scroll < 0)
		{
			cs->scroll = 0;
			print_cmdline(cs);
		}
		move_cs(&cs);
	}
}

void	arrow_down(t_cs_line *cs)
{
	int	scroll;

	if (cs)
	{
		scroll = cs->scroll;
		if (cs->line_col + cs->screen.x <= (int)ft_strlen(cs->input))
			cs->line_col += cs->screen.x;
		else
			cs->line_col = (int)ft_strlen(cs->input);
		cs->cr = get_line(cs);
		if (cs->cr - cs->scroll + cs->min_row >= cs->screen.y)
		{
			cs->scroll = cs->cr - (cs->screen.y - (cs->min_row + (cs->screen.x
						> 2 ? 0 : 1) + (cs->scroll > 0 ? 1 : 0)) - 1);
			print_cmdline(cs);
		}
		if (cs->scroll < 0)
			cs->scroll = 0;
		move_cs(&cs);
	}
}

void	arrow_right(t_cs_line *cs)
{
	if (cs)
	{
		if (cs->line_col < (int)ft_strlen(cs->input))
			cs->line_col += 1;
		if (cs->col == cs->screen.x - 1 && cs->row >= cs->screen.y - 1)
		{
			cs->scroll += 1;
			print_cmdline(cs);
		}
		if (cs->scroll < 0)
			cs->scroll = 0;
		move_cs(&cs);
	}
}

void	arrow_left(t_cs_line *cs)
{
	if (cs)
	{
		if (cs->line_col > 0)
			cs->line_col -= 1;
		if (cs->col == 1 && cs->scroll && cs->row == cs->min_row
				+ (cs->screen.x > 1 ? 0 : 1) + (cs->scroll > 0 ? 1 : 0))
		{
			cs->scroll -= 1;
			print_cmdline(cs);
		}
		if (cs->scroll < 0)
			cs->scroll = 0;
		move_cs(&cs);
	}
}
