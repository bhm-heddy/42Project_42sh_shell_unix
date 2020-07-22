#include "libft.h"
#include "ft_printf.h"
#include "exec.h"
#include "sh.h"

static char		*state(t_job *j, uint8_t opt)
{
	char	*tab[4];
	char	*tab_opt[4];
	int16_t	s_ret;

	tab[0] = S_SIGSTOP;
	tab[1] = S_SIGTSTP;
	tab[2] = S_SIGTTIN;
	tab[3] = S_SIGTTOU;
	tab_opt[0] = "Stopped (signal)    ";
	tab_opt[1] = "Stopped             ";
	tab_opt[2] = "Stopped (tty input) ";
	tab_opt[3] = "Stopped (tty output)";
	if (j->status & RUNNING)
		return ("Running\t");
	s_ret = j->ret - 19 - 128;
	if (s_ret > -1 && s_ret < 4)
	{
		if (!opt)
			return (tab[s_ret]);
		return (tab_opt[s_ret]);
	}
	return ("Stopped\t");
}

static void		print_this_job(t_job *j, uint8_t curr, char opt)
{
	char bg;

	bg = (j->fg) ? '\0' : '&';
	curr = (curr > 45) ? 32 : curr;
	if (opt == 'p')
		ft_printf("%d\n", j->pgid);
	else if (opt == 'l')
		ft_printf("[%d]%c  %d %s %s %c\n",
				j->id, curr, j->pgid, state(j, 1), j->cmd, bg);
	else
		ft_printf("[%d]%c  %s \t %s %c\n",
				j->id, curr, state(j, 0), j->cmd, bg);
}

uint8_t			print_all_jobs(t_cfg *shell, t_list *jobs, char opt)
{
	uint8_t		i;
	uint8_t		c;
	t_job		*j;
	t_list		*tmp;

	i = 0;
	while (i++ < shell->active_job)
	{
		c = 43;
		tmp = jobs;
		while (tmp && (j = tmp->data) && j->id != i && (c += 2))
			tmp = tmp->next;
		if (tmp)
			print_this_job(j, c, opt);
	}
	return (SUCCESS);
}

uint8_t			print_jobs(t_cfg *shell, t_process *p, char opt, int32_t ac)
{
	uint8_t		i;
	uint8_t		err;
	uint8_t		curr;
	t_job		*j;

	i = 0;
	err = 0;
	j = 0;
	while (p->av[ac])
	{
		curr = 41;
		if (get_job(shell->job, p->av[ac], &j, &curr) == SUCCESS)
			print_this_job(j, curr, opt);
		else
		{
			ft_dprintf(STDERR_FILENO, "%s: jobs: %s", PROJECT, p->av[ac]);
			ft_dprintf(STDERR_FILENO, ": no such job\n");
			err++;
		}
		ac++;
	}
	return (err ? 1 : 0);
}
