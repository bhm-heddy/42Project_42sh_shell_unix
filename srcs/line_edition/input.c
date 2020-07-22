#include "libft.h"
#include "struct.h"
#include "line_edition.h"

void			join_input(t_cs_line *cs, char *input)
{
	char	*tmp;
	char	*insert;
	char	oc;

	if (cs && input)
	{
		if ((int)ft_strlen(cs->input) == cs->line_col && (tmp = cs->input))
		{
			cs->input = ft_strjoin(cs->input, input);
			ft_strdel(&tmp);
		}
		else if (cs->input && cs->input[0])
		{
			oc = cs->input[cs->line_col];
			cs->input[cs->line_col] = '\0';
			tmp = cs->input;
			cs->input = ft_strjoin(tmp, input);
			tmp[cs->line_col] = oc;
			insert = cs->input;
			cs->input = ft_strjoin(insert, &tmp[cs->line_col]);
			ft_strdel(&insert);
			ft_strdel(&tmp);
		}
		ft_utoa(&cs->input);
	}
}

void			line_master(t_cs_line *cs, char *input)
{
	char	*tmp;

	if (input && cs)
	{
		if (ft_strcmp(input, "\n") == 0 || input[0] == '\n')
		{
			tmp = cs->input;
			cs->input = ft_strjoin(tmp, "\n");
			ft_strdel(&tmp);
		}
		else
		{
			join_input(cs, input);
			cs->line_col += (int)ft_strlen(input);
			cs->max_scroll = (int)ft_strlen(cs->input) / cs->screen.x
				- (cs->screen.y - cs->min_row);
			set_scroll(cs);
		}
		cs->history->data = cs->input;
		cs->clipb = (t_point){-1, -1};
	}
}

static t_point	input_trimmer(t_cs_line *cs, t_point z, int col_prompt)
{
	int		line;
	t_point	i;

	line = 0;
	i = (t_point){0, 0};
	while (cs->input[i.x])
	{
		i.y++;
		if (((line == 0 && i.y + cs->min_col + ((int)ft_strlen(cs->prompt)
			> cs->screen.x ? (int)ft_strlen(cs->prompt) : 0))
			> cs->screen.x || i.y >= cs->screen.x) && ++line)
			i.y = 0;
		if (cs->scroll > 0 && line > cs->scroll && !z.x && (z.x = i.x + 1))
			ft_putstr_fd("\e[0;31m\e[47m\e[1m\e[4m\e[7m^\e[0m\n", cs->tty);
		if (line - cs->scroll + cs->min_row + (((int)ft_strlen(cs->prompt)
			> cs->screen.x && !cs->scroll) ? 1 : 0) >= cs->screen.y
			&& (z.y = i.x - 1 - ((int)ft_strlen(cs->prompt)
			< cs->screen.x && cs->scroll == 0 ? col_prompt : 0)) >= 0)
			break ;
		i.x++;
	}
	return (z);
}

t_point			trim_input(t_cs_line *cs)
{
	t_point	z;
	t_point	i;
	int		line;
	int		col_prompt;

	z = (t_point){0, 0};
	if (cs && cs->input && (z.y = (int)ft_strlen(cs->input)) >= 0)
	{
		i = (t_point){0, 0};
		line = 0;
		col_prompt = (int)ft_strlen(cs->prompt);
		col_prompt -= (col_prompt > cs->screen.x ? cs->screen.x : 0);
		z = input_trimmer(cs, z, col_prompt);
	}
	return (z);
}
