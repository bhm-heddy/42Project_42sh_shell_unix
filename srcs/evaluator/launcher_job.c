#include "libft.h"
#include "exec.h"
#include "var.h"
#include "job_control.h"
#include "sh.h"

void		routine_process(t_cfg *shell, t_list *process, t_pipe *fd)
{
	t_process	*manage;
	t_list		*env;

	env = shell->env;
	manage = process->data;
	if (env)
		manage->env = ft_lstdup(env, env->size, cpy_var_list);
	fd->tmp = fd->fd[0];
	fd->fd[0] = 0;
	fd->fd[1] = 0;
	if (!process->next)
		return ;
	if (pipe(fd->fd) == -1)
		ft_ex(EX);
	manage->std[1] = fd->fd[1];
	manage->setup |= PIPE_ON;
	manage = process->next->data;
	manage->std[0] = fd->fd[0];
	manage->setup |= PIPE_ON;
}

void		routine_fg_job(t_cfg *shell, t_job *j)
{
	shell->cur_job = j->pgid;
	wait_process(j);
	shell->cur_job = 0;
	tcsetpgrp(STDIN_FILENO, shell->pid);
	if (set_termios(TCSADRAIN, &shell->term_origin) == FAILURE)
		ft_ex(EXUEPTD);
}

void		update_last_return(t_cfg *shell, uint8_t jret)
{
	char	*sp_ret;

	sp_ret = ft_itoa(jret);
	setvar_update(find_var(shell->sp, "?"), sp_ret);
	ft_strdel(&sp_ret);
}

uint8_t		routine_ending_job(t_cfg *shell, t_job *job)
{
	if (!shell->interactive)
		wait_process(job);
	else if (job->fg)
		routine_fg_job(shell, job);
	else
		set_job_background(job);
	debug_print_job(shell->debug, job, "Ending job");
	update_last_return(shell, job->ret);
	return (job->ret);
}

uint8_t		run_job(t_cfg *shell, t_job *job, t_list *process)
{
	job->status |= RUNNING;
	ft_lstiter(job->process, job_redir);
	while (process)
	{
		routine_process(shell, process, &job->pipe);
		run_process(shell, job, process->data);
		process = process->next;
		if (job->pipe.tmp)
			if (close(job->pipe.tmp) == -1)
				ft_ex(EXUEPTD);
	}
	return (routine_ending_job(shell, job));
}
