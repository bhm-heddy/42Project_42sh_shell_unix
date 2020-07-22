#include "line_edition.h"
#include "struct.h"

void	history_up(t_cs_line *cs)
{
	if (cs)
	{
		if (cs->history->prev && cs->history->prev->data)
		{
			ft_clear(1);
			cs->clipb = (t_point){-1, -1};
			cs->history = cs->history->prev;
			ft_strdel(&cs->old_history);
			cs->old_history = ft_strdup((char *)cs->history->data);
			cs->input = (char *)cs->history->data;
			cs->line_col = ft_strlen(cs->input);
			cs->scroll = 0;
			set_scroll(cs);
			print_cmdline(cs);
		}
	}
}

void	history_down(t_cs_line *cs)
{
	if (cs)
	{
		if (cs->history->next && cs->history->next->data)
		{
			ft_clear(1);
			cs->clipb = (t_point){-1, -1};
			cs->history = cs->history->next;
			ft_strdel(&cs->old_history);
			cs->old_history = ft_strdup((char *)cs->history->data);
			cs->input = (char *)cs->history->data;
			cs->line_col = ft_strlen(cs->input);
			cs->scroll = 0;
			print_cmdline(cs);
		}
	}
}
