#include "libft.h"
#include "ft_printf.h"
#include "sh.h"
#include "job_control.h"
#include "exec.h"
#include <signal.h>

static uint8_t	fg_opt(uint8_t interactive, t_process *p, int32_t *ac)
{
	int32_t		i;
	int8_t		ret;

	i = 0;
	if (!interactive || (p->setup & PIPE_ON))
	{
		ft_dprintf(STDERR_FILENO, "fg: no job control\n");
		return (FAILURE);
	}
	while ((ret = ft_getopt(ac, &i, p->av, "")) != -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: fg: %c: invalide option\n%s\n",
				PROJECT, p->av[*ac][i], FG_USG);
		return (FAILURE);
	}
	return (SUCCESS);
}

uint8_t			find_target(t_list *ljob, char *wanted,
							t_job **target, char *blt)
{
	uint8_t		curr;
	int8_t		ret;

	ret = 0;
	if (wanted)
	{
		if ((ret = get_job(ljob, wanted, target, &curr)) == FAILURE)
			ft_dprintf(STDERR_FILENO, "%s: %s: %s: no such job\n",
					PROJECT, blt, wanted);
	}
	else if ((ret = get_job(ljob, "%", target, &curr)) == FAILURE)
		ft_dprintf(STDERR_FILENO, "%s: %s: current: no such job\n",
					PROJECT, blt);
	return (ret);
}

static uint8_t	put_job_in_fg(t_cfg *shell, t_job *target)
{
	t_job		*jcpy;
	uint32_t	tmp;
	uint8_t		ret;

	jcpy = malloc(sizeof(t_job));
	protect_malloc(jcpy);
	tmp = shell->cur_job;
	job_is_running(target);
	target->fg = TRUE;
	ft_cpy_job(target, jcpy);
	ft_lstdelif(&shell->job, &target->pgid, focus_job, del_struct_job);
	ft_printf("%s\n", jcpy->cmd);
	tcsetpgrp(STDIN_FILENO, jcpy->pgid);
	if (set_termios(TCSADRAIN, &jcpy->term_eval) == FAILURE)
		ft_ex(EXUEPTD);
	kill(-jcpy->pgid, SIGCONT);
	routine_fg_job(shell, jcpy);
	shell->cur_job = tmp;
	if (!(jcpy->status & STOPPED))
		nb_job_active(shell);
	ret = jcpy->ret;
	del_struct_job(jcpy, sizeof(t_job));
	return (ret);
}

uint8_t			ft_fg(t_process *p)
{
	t_cfg		*shell;
	t_job		*target;
	int32_t		ac;
	uint8_t		ret;

	target = 0;
	shell = cfg_shell();
	ac = 1;
	if (fg_opt(shell->interactive, p, &ac) != SUCCESS)
		return (2);
	if (find_target(shell->job, p->av[ac], &target, "fg") != SUCCESS)
		return (1);
	ret = put_job_in_fg(shell, target);
	return (ret);
}
