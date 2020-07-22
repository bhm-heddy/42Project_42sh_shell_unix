#include "libft.h"
#include "get_next_line.h"
#include "line_edition.h"
#include "struct.h"
#include <stdlib.h>
#include <sh.h>

void	copy_clip(t_cs_line *cs)
{
	if (cs)
	{
		if (cs->clipb.x > -1 && cs->clipb.y > -1 && cs->clipb.y
			- cs->clipb.x > 0)
		{
			ft_strdel(&cfg_shell()->clipboard);
			cfg_shell()->clipboard = ft_strsub(cs->input, cs->clipb.x,
			cs->clipb.y - cs->clipb.x);
		}
	}
}

void	paste_clip(t_cs_line *cs)
{
	if (cs && cfg_shell()->clipboard)
	{
		line_master(cs, cfg_shell()->clipboard);
		cs->clipb = (t_point){0, 0};
		print_cmdline(cs);
	}
}

void	cut_clip(t_cs_line *cs)
{
	char	*cut;
	char	*tmp;
	char	oc;

	copy_clip(cs);
	if (cs->clipb.x != -1 && cs->clipb.y != -1 && cs->clipb.y - cs->clipb.x > 0)
	{
		ft_clear(1);
		oc = cs->input[cs->clipb.x];
		cs->input[cs->clipb.x] = '\0';
		cut = ft_strdup(cs->input);
		cs->input[cs->clipb.x] = oc;
		tmp = cut;
		cs->line_col = cs->clipb.x;
		cut = ft_strjoin(cut, &cs->input[cs->clipb.y]);
		ft_strdel(&tmp);
		ft_strdel(&cs->input);
		cs->input = cut;
		cs->clipb = (t_point){-1, -1};
		print_cmdline(cs);
	}
}
