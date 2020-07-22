#include "libft.h"
#include "exec.h"
#include "job_control.h"
#include "sh.h"

void			add_job_cfg(t_job *job)
{
	t_cfg	*shell;
	t_job	jc;

	shell = cfg_shell();
	if (!job->id)
	{
		shell->active_job++;
		job->id = shell->active_job;
	}
	ft_cpy_job(job, &jc);
	if (job->status & STOPPED)
		ft_lst_push_front(&shell->job, &jc, sizeof(t_job));
	else
		insert_running_job(shell, shell->job, &jc);
	ft_bzero(&jc, sizeof(t_job));
	debug_print_job(shell->debug, &jc, "add_job_cfg");
}

void			ft_cpy_job(t_job *job, t_job *copy)
{
	ft_bzero(copy, sizeof(t_job));
	copy->cmd = ft_strdup(job->cmd);
	copy->process =
		ft_lstdup(job->process, job->process->size, cpy_lst_process);
	copy->pgid = job->pgid;
	copy->fg = job->fg;
	copy->status = job->status;
	copy->ret = job->ret;
	copy->id = job->id;
	ft_memset(copy->std, -1, sizeof(int16_t) * 3);
	ft_memcpy(&copy->term_eval, &job->term_eval, sizeof(job->term_eval));
}
