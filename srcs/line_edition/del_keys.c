#include "libft.h"
#include "struct.h"
#include "line_edition.h"

void	back_space(t_cs_line *cs)
{
	char	*oc;
	char	*tmp2;

	if (cs->line_col > 0 && (tmp2 = cs->input))
	{
		if (cs->line_col > 0)
		{
			oc = &tmp2[cs->line_col - 1];
			*oc = '\0';
			if (tmp2[cs->line_col] != '\0')
				cs->input = ft_strjoin(tmp2, &tmp2[cs->line_col]);
			else
				cs->input = ft_strdup(tmp2);
			ft_strdel(&tmp2);
			cs->history->data = (void *)cs->input;
		}
		cs->line_col -= (cs->line_col > 0 ? 1 : 0);
		if (cs->col == 1 && cs->scroll && cs->row == cs->min_row
				+ (cs->screen.x > 1 ? 0 : 1) + (cs->scroll > 0 ? 1 : 0))
			cs->scroll -= 2;
		cs->scroll = (cs->scroll < 0 ? 0 : cs->scroll);
		print_cmdline(cs);
	}
}

int		revback_space(t_cs_line *cs)
{
	char	*oc;
	char	*tmp2;

	if (cs)
	{
		if ((tmp2 = cs->input) && tmp2[0])
		{
			if (cs->line_col < (int)ft_strlen(cs->input))
			{
				oc = &tmp2[cs->line_col];
				*oc = '\0';
				if (tmp2[cs->line_col + 1] != '\0')
					cs->input = ft_strjoin(tmp2, &tmp2[cs->line_col + 1]);
				else
					cs->input = ft_strdup(tmp2);
				ft_strdel(&tmp2);
			}
			print_cmdline(cs);
		}
		return (1);
	}
	return (-1);
}
