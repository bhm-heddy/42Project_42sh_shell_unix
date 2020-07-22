#include "libft.h"
#include "exec.h"
#include "sh.h"
#include "ft_printf.h"
#include "job_control.h"
#include <sys/wait.h>

void			aplylyse_wstatus(t_process *p, int wstatus)
{
	if (WIFEXITED(wstatus))
	{
		p->ret = WEXITSTATUS(wstatus);
		p->status = p->ret & (126 | 127) ? FAILED : COMPLETED;
	}
	else if (WIFSIGNALED(wstatus))
	{
		p->status = KILLED;
		p->ret = WTERMSIG(wstatus);
	}
	else if (WIFSTOPPED(wstatus))
	{
		p->status = STOPPED;
		p->ret = WSTOPSIG(wstatus);
	}
	else if (WIFCONTINUED(wstatus))
		p->status = RUNNING;
}

void			update_process(t_list *lst, pid_t child, int wstatus)
{
	t_process *p;

	if (child == -1)
		return ;
	p = find_process_by_pid(lst, child);
	aplylyse_wstatus(p, wstatus);
}

static void		update_job(t_job *j)
{
	t_list		*lst;
	t_process	*tmp;

	if ((tmp = find_process_by_status(j->process, STOPPED)))
	{
		j->ret = 128 + tmp->ret;
		j->status = STOPPED;
		add_job_cfg(j);
		print_message_signal(j->ret - 128, j, 0);
	}
	else
	{
		lst = ft_lstgettail(j->process);
		tmp = lst->data;
		j->status = ((t_process *)(lst->data))->status;
		if (j->status == KILLED)
			j->ret = print_message_signal(tmp->ret, j, 0);
		else
			j->ret = tmp->ret;
	}
}

void			wait_process(t_job *job)
{
	pid_t		pid_child;
	int32_t		wstatus;

	debug_print_all_process(job->process, "Before Wait");
	while (ft_lsthave(job->process, has_running))
	{
		wstatus = 0;
		pid_child = waitpid(-job->pgid, &wstatus, WUNTRACED);
		update_process(job->process, pid_child, wstatus);
	}
	update_job(job);
	debug_print_all_process(job->process, "After Wait");
	return ;
}
