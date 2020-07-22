#include "ft_printf.h"
#include "struct.h"
#include "sh.h"

void	debug_print_job(int32_t fd_debug, t_job *j, char *where)
{
	if (!fd_debug)
		return ;
	ft_dprintf(fd_debug, "\t----> [Print JOB]  [%s]\n", where);
	ft_dprintf(fd_debug, "CMD = [%s]\tID = [%d]\tFG = [%d]\n",
			j->cmd, j->id, j->fg);
	ft_dprintf(fd_debug, "STATUS = [%d]\tRET = [%d]]\n",
			j->status, j->ret);
	ft_dprintf(fd_debug, "-----------\n");
}

void	debug_print_process(int32_t fd_debug, t_process *p, char *where)
{
	int16_t		*t;
	t_list		*fd;

	if (!fd_debug)
		return ;
	fd = p->fd;
	ft_dprintf(fd_debug, "\t----> [Print Process]  [%s]\n", where);
	ft_dprintf(fd_debug, "CMD = [%s]\tPATH = [%s]\tPID = [%d]\n",
			p->cmd, p->path, p->pid);
	ft_dprintf(fd_debug, "SETUP = [%032b]\n", p->setup);
	ft_dprintf(fd_debug, "STATUS = [%d]\t RET = [%d]\n",
		p->status, p->ret);
	if (!fd)
		ft_dprintf(fd_debug, "No redirection in all process job\n");
	while (fd)
	{
		t = fd->data;
		ft_dprintf(fd_debug, "fd[0] = [%d]\tfd[1] = [%d]\n", t[0], t[1]);
		fd = fd->next;
	}
}

void	debug_print_all_process(t_list *process, char *where)
{
	t_cfg		*shell;

	shell = cfg_shell();
	if (!shell->debug)
		return ;
	ft_dprintf(shell->debug,
			"\n\n-----------\t [DEBUG] [All Process]\t[%s]\n", where);
	while (process)
	{
		debug_print_process(shell->debug, process->data, 0);
		process = process->next;
	}
	ft_dprintf(shell->debug, "\n");
}

void	debug_print_all_job(t_list *job, char *where)
{
	t_cfg		*shell;

	shell = cfg_shell();
	if (!shell->debug)
		return ;
	ft_dprintf(shell->debug,
			"\n\n-----------\t [DEBUG] [All Job]\t[%s]\n", where);
	while (job)
	{
		debug_print_job(shell->debug, job->data, 0);
		job = job->next;
	}
}

void	debug_print_everything(t_list *job, char *where)
{
	t_cfg		*shell;
	t_job		*j;

	shell = cfg_shell();
	if (!shell->debug)
		return ;
	ft_dprintf(shell->debug,
			"\n\n-----------\t [DEBUG] [EveryThings]\t[%s]\n", where);
	while (job)
	{
		j = job->data;
		debug_print_job(shell->debug, j, 0);
		debug_print_all_process(j->process, where);
		job = job->next;
	}
}
