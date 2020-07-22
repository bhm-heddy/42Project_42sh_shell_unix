#include "exec.h"
#include <signal.h>
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "line_edition.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "struct.h"
#include "sh.h"

void	size_handler(int sig)
{
	t_cs_line	*cs;
	int			cr;

	if (sig == SIGWINCH && (cs = cs_master(NULL, 0)))
	{
		cs->min_row = 0;
		cs->min_col = 0;
		ft_clear(1);
		cs_set();
		cr = get_line(cs);
		cs->cr = cr;
		cs->scroll = cs->cr - (cs->screen.y - cs->min_row - 1);
		if (cs->scroll < 0)
			cs->scroll = 0;
		print_cmdline(cs);
	}
}

void	sig_handler(int sig)
{
	t_cs_line		*cs;
	struct termios	new_term;

	if (sig >= 0 && (cs = cs_master(NULL, 0)))
	{
		tcgetattr(cs->tty, &new_term);
		new_term.c_cc[VMIN] = 0;
		tcsetattr(cs->tty, TCSANOW, &new_term);
		cs->sig_int = (sig > 0 ? 1 : 0);
		history_search(cs, "\0");
		ft_strdel(&cs->old_history);
	}
}

void	sigterm_handler(int sig)
{
	t_process p;

	(void)sig;
	ft_bzero(&p, sizeof(t_process));
	if (!(p.av = ft_memalloc(sizeof(char *) * 2)))
		ft_ex(EXMALLOC);
	ft_exit(&p);
	ft_memdel((void **)&p.av);
}

void	init_signals(void)
{
	int	i;

	i = 0;
	while (i <= 32)
	{
		if (i == SIGCONT || i == SIGTSTP || i == SIGTTIN)
			signal(i, SIG_IGN);
		else if (i == SIGWINCH)
			signal(i, size_handler);
		i++;
	}
}
