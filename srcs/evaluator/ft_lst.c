#include "exec.h"
#include "libft.h"

int32_t		has_stopped(t_list *lst)
{
	t_process *p;

	p = lst->data;
	if (p->status & STOPPED)
		return (1);
	return (0);
}

int32_t		has_running(t_list *lst)
{
	t_process *p;

	p = lst->data;
	if (p->status & RUNNING)
		return (1);
	return (0);
}

void		close_fd(t_list *lst)
{
	int16_t	*fd;

	fd = lst->data;
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
}

void		job_redir(t_list *process)
{
	t_process *p;

	p = process->data;
	p->setup |= process_redir(p, p->redir);
}
