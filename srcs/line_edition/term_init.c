#include <signal.h>
#include <termios.h>
#include <term.h>
#include "line_edition.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "struct.h"
#include "sh.h"
#include "var.h"

void	set_term(int tty, char *prompt, struct termios *new_term)
{
	t_cs_line			*cs;

	(*new_term).c_lflag &= ~(ICANON | ECHO);
	(*new_term).c_cc[VMIN] = 1;
	(*new_term).c_cc[VTIME] = 0;
	tcsetattr(tty, TCSANOW, new_term);
	cs_master(prompt, 1);
	cs = cs_master(NULL, 0);
	get_cs_line_position(&cs->min_col, &cs->min_row);
	cs_set();
	if (cs->min_row >= cs->screen.y - 1)
	{
		cs->min_row -= 1;
		ft_putstr_fd("\n", cs->tty);
	}
	if (cs->min_col > 0)
	{
		if (cs->min_row >= cs->screen.y - 1)
			ft_putstr_fd("\n", cs->tty);
		else
			cs->min_row += 1;
		cs->min_col = 0;
	}
	cs->tty = tty;
	move_cs(&cs);
}

void	unset_term(struct termios *old_term)
{
	t_cs_line	*cs;

	if ((cs = cs_master(NULL, 0)))
	{
		tcsetattr(cs->tty, 0, old_term);
	}
}

int		term_check(struct termios *new_term, int tty)
{
	int		ret;
	char	*term;
	t_cfg	*cfg;

	ret = 0;
	if ((cfg = cfg_shell()))
	{
		ret = 1;
		if (!isatty(tty) && !(ret = 0))
			ft_putstr_fd("21sh: Not a valid terminal type device\n", 2);
		if (ret && (!(term = find_var_value(cfg->env, "TERM"))
			|| tgetent(NULL, term) <= 0 || ft_strcmp(term, "dumb") == 0))
			term = "vt100";
		if (ret && tgetent(NULL, term) == -1 && !(ret = 0))
			ft_putstr_fd("21sh: Terminfo database not found\n", 2);
		if (ret && (tcgetattr(tty, new_term) == -1) && !(ret = 0))
			ft_putstr_fd("21sh: Could not get terminal attributes\n", 2);
		init_signals();
	}
	return (ret);
}

int		term_init(int init, char *prompt)
{
	struct termios			new_term;
	int						tty;
	t_cfg					*cfg;

	tty = ttyslot();
	if ((cfg = cfg_shell()) && !cfg->interactive)
		if ((tty = open(cfg->file, O_RDONLY)) < 0)
			return (-1);
	if (!cfg->interactive)
		return (1);
	if (init >= 1 && term_check(&new_term, tty) == 1)
	{
		set_term(tty, prompt, &new_term);
		return (1);
	}
	if (init == 0)
	{
		unset_term(&cfg->term_origin);
		return (1);
	}
	return (0);
}
