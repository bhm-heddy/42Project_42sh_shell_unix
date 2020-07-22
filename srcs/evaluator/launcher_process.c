#include "libft.h"
#include "ft_printf.h"
#include "exec.h"
#include "var.h"
#include "sh.h"

static void			kick_off_child(t_process *p, char **envp)
{
	if (p->setup & ERROR)
	{
		ft_dprintf(STDERR_FILENO, "%s", p->message);
		exit(p->ret);
	}
	if (p->setup & BUILTIN)
		exit(builtin_process(p));
	if (p->setup & NOCMD)
		exit(0);
	if ((execve(p->path, p->av, envp)) == -1)
		ft_ex(EXEXEC);
}

static uint8_t		parent_process(t_job *job, t_process *process,
		int fd_pipe, char **envp)
{
	if (fd_pipe)
		if (close(fd_pipe) == -1)
			ft_ex(EXUEPTD);
	if (cfg_shell()->interactive)
	{
		if (job->pgid == 0)
			job->pgid = process->pid;
		setpgid(process->pid, job->pgid);
		if (job->fg)
			if (tcsetpgrp(STDIN_FILENO, job->pgid))
				ft_ex(EX);
	}
	ft_del_tab((void **)envp);
	return (SUCCESS);
}

static uint8_t		child_process(t_job *job, t_process *p,
		int fd_pipe, char **envp)
{
	if (fd_pipe)
		if (close(fd_pipe) == -1)
			ft_ex(EXUEPTD);
	p->pid = getpid();
	if (cfg_shell()->interactive)
	{
		if (job->pgid == 0)
			job->pgid = p->pid;
		setpgid(p->pid, job->pgid);
		if (job->fg)
			if (tcsetpgrp(STDIN_FILENO, job->pgid) == -1)
				ft_ex(EX);
	}
	set_signal_child();
	do_pipe(p);
	do_redir(p->fd);
	kick_off_child(p, envp);
	exit(1);
}

static uint8_t		fork_process(t_job *job, t_process *p)
{
	char	**envp;

	envp = create_tab_var(p->env, 0);
	if ((p->pid = fork()) == -1)
		ft_ex(EX);
	if (!(p->pid))
		return (child_process(job, p, job->pipe.fd[0], envp));
	if (p->pid)
		return (parent_process(job, p, job->pipe.fd[1], envp));
	return (0);
}

void				run_process(t_cfg *shell, t_job *j, t_process *p)
{
	p->status = RUNNING | (p->status & ~WAITING);
	process_type(p);
	process_assign(shell, p, p->assign);
	debug_print_process(shell->debug, p, "Run_Process");
	if (p->setup & BUILTIN && !(p->setup & PIPE_ON) && j->fg)
	{
		builtin_save_fd(j);
		do_redir(p->fd);
		if (p->setup & R_ERROR)
			ft_dprintf(STDERR_FILENO, "%s", p->message);
		if ((p->setup & R_ERROR) &&
				(p->setup & B_SPECIAL) && !shell->interactive)
			exit(1);
		builtin_process(p);
		builtin_restor_fd(j);
	}
	else
		fork_process(j, p);
	ft_lstiter(p->fd, close_fd);
	return ;
}
