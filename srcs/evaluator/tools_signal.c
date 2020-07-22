#include "ft_printf.h"
#include "libft.h"
#include "exec.h"

char		**create_message_signal(char **tab)
{
	ft_bzero(tab, sizeof(char *) * 32);
	tab[1] = S_SIGHUP;
	tab[2] = S_SIGINT;
	tab[3] = S_SIGQUIT;
	tab[4] = S_SIGILL;
	tab[5] = S_SIGTRAP;
	tab[6] = S_SIGABRT;
	tab[7] = S_SIGBUS;
	tab[8] = S_SIGFPE;
	tab[9] = S_SIGKILL;
	tab[10] = S_SIGUSR1;
	tab[11] = S_SIGSEGV;
	tab[12] = S_SIGUSR2;
	tab[14] = S_SIGALRM;
	tab[15] = S_SIGTERM;
	tab[19] = S_SIGSTOP;
	tab[20] = S_SIGTSTP;
	tab[21] = S_SIGTTIN;
	tab[22] = S_SIGTTOU;
	tab[24] = S_SIGXCPU;
	tab[25] = S_SIGXFSZ;
	tab[26] = S_SIGALRM;
	tab[27] = S_SIGPROF;
	tab[31] = S_SIGSYS;
	return (tab);
}

uint8_t		print_message_signal(uint8_t sig, t_job *j, t_process *p)
{
	char	*tab[32];

	create_message_signal(tab);
	if (j)
	{
		if ((sig < 19 || sig > 22) && tab[sig] && j->fg)
			ft_dprintf(STDERR_FILENO, "%s\n", tab[sig]);
		else if (tab[sig])
			ft_dprintf(STDERR_FILENO,
					"[%d]\t+ %s  %s\n", j->id, tab[sig], j->cmd);
		return (sig + 128);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "%s\t%s\n", tab[sig], p->cmd);
		return (sig + 128);
	}
}

void		one_process_change(t_process *p)
{
	if (p->status & (STOPPED | KILLED))
		print_message_signal(p->ret, 0, p);
}
