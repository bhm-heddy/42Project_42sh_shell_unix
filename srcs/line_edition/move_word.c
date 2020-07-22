#include "line_edition.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <sys/ioctl.h>
#include "struct.h"

void	mv_word_left(t_cs_line *cs)
{
	int		i;
	char	*s;

	if (cs && cs->line_col > 0 && (s = cs->input))
	{
		i = cs->line_col - 1;
		while (i > 0 && (s[i] == ' ' || s[i] == '\t'))
			i--;
		while (i > 0 && s[i] != ' ' && s[i] != '\t' && s[i - 1] != ' '
				&& s[i - 1] != '\t')
			i--;
		cs->line_col = i;
		cs->cr = get_line(cs);
		if (cs->cr + cs->min_row - cs->scroll - 1 <= cs->min_row + (cs->scroll
			|| cs->screen.x <= (int)ft_strlen(cs->prompt)) && cs->scroll)
		{
			cs->scroll = cs->cr - (cs->screen.y - (cs->min_row + (cs->screen.x
						> 2 ? 0 : 1) + (cs->scroll > 0 ? 1 : 0)) - 1);
			print_cmdline(cs);
		}
		if (cs->scroll < 0 && (cs->scroll = 0) == 0)
			print_cmdline(cs);
		move_cs(&cs);
	}
}

void	mv_word_right(t_cs_line *cs)
{
	int		i;
	int		max;
	char	*s;

	if (cs && (s = cs->input))
	{
		i = cs->line_col;
		max = ft_strlen(cs->input);
		while (i < max && s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		while (i < max && s[i] && !(s[i] == ' ' || s[i] == '\t'))
			i++;
		cs->line_col = i;
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
