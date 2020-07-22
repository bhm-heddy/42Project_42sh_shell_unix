#include "line_edition.h"
#include "struct.h"
#include "libft.h"

static void	get_pos(t_cs_line *cs, t_point *i, t_point *j, int len)
{
	if (cs && i && j)
	{
		while (i->x < cs->line_col || (i->x == cs->line_col && cs->scroll > 0
				&& cs->screen.x > 0))
		{
			if ((cs->input[i->x] == '\n' || i->y == cs->screen.x || (j->x == 0
				&& !cs->scroll && cs->screen.x > len && i->y + cs->min_col
				>= cs->screen.x)) && ++j->x)
				i->y = 0;
			*i = (t_point){i->x + 1, i->y + 1};
		}
	}
}

t_point		cs_pos(t_cs_line *cs)
{
	t_point pos;
	t_point i;
	t_point	j;
	int		len;

	i = (t_point){0, 0};
	pos = (t_point){0, 0};
	if (cs && cs->input && cs->input[0])
	{
		len = (int)ft_strlen(cs->prompt);
		j = (t_point){0, cs->min_col};
		cs->min_col += len;
		if (cs->scroll || cs->screen.x <= len)
			cs->min_col = 0;
		get_pos(cs, &i, &j, len);
		i.y = (i.y > cs->line_col ? cs->line_col : i.y);
		pos.x = i.y + (j.x == 0 && cs->screen.x > len ? cs->min_col : 0)
			- (cs->scroll ? 1 : 0);
		pos.y = j.x - cs->scroll + cs->min_row + (!cs->scroll && cs->screen.x
				<= len ? 1 : 0);
		cs->min_col = j.y;
	}
	return (pos);
}

int			get_line(t_cs_line *cs)
{
	t_point i;
	t_point cr;

	cr = (t_point){0, 0};
	if (cs->input && cs->input[0])
	{
		i = (t_point){cs->line_col, 0};
		while (cs->input[i.x] && cr.x == 0 && i.y++ >= 0)
		{
			if ((i.y == cs->screen.x || (i.x + cs->min_col
				+ (int)ft_strlen(cs->prompt) == cs->screen.x)) && ++cr.x)
				i.y = 0;
			i.x++;
		}
		i = (t_point){0, 0};
		cr.y = cr.x;
		while (i.x < cs->line_col && i.y++ >= 0)
		{
			if ((i.y == cs->screen.x || (i.x + cs->min_col
				+ (int)ft_strlen(cs->prompt) == cs->screen.x)) && ++cr.x)
				i.y = 0;
			i.x++;
		}
	}
	return (cr.x);
}

void		position_reader(char *buf, t_cs_line *cs)
{
	int	i;

	i = 0;
	if (buf && cs)
	{
		while (i <= 31)
		{
			if (read(cs->tty, &buf[i], 1) != 1 || buf[i] == 'R')
				break ;
			if (buf[i] == '\n')
				i -= 1;
			i++;
		}
		buf[i] = '\0';
	}
}

void		get_cs_line_position(int *col, int *row)
{
	char		buf[33];
	char		**n;
	t_cs_line	*cs;

	ft_bzero(&buf, 32);
	cs = cs_master(NULL, 0);
	if (read(cs->tty, &buf, 0) == -1)
		return ;
	write(cs->tty, "\033[6n", ft_strlen("\033[6n"));
	position_reader(&buf[0], cs);
	if (!(n = split_pos(buf)))
	{
		*col = 0;
		*row = 0;
		return ;
	}
	*row = ft_atoi(n[0]) - 1;
	*col = ft_atoi(n[1]) - 1;
	ft_strdel(&n[0]);
	ft_strdel(&n[1]);
	free(n);
}
