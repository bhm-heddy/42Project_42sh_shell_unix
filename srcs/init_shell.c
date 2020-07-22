#include "exec.h"
#include "var.h"
#include "sh.h"
#include "struct.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

void		set_var(t_cfg *shell)
{
	char	*sl;
	char	*pid;

	pid = ft_itoa(shell->pid);
	setvar_add(&shell->sp, "$", pid);
	setvar_add(&shell->sp, "?", "0");
	setvar_add(&shell->sp, "!", "0");
	setvar_add(&shell->sp, "*", 0);
	setvar_add(&shell->sp, "@", 0);
	setvar_add(&shell->sp, "#", 0);
	setvar_add(&shell->sp, "-", 0);
	setvar_add(&shell->sp, "0", 0);
	setvar_add(&shell->env, "HISTSIZE", "32767");
	ft_strdel(&pid);
	ft_setvar(&shell->intern, "PS1", NAME_SH);
	ft_setvar(&shell->intern, "PS2", "> ");
	sl = ft_itoa(ft_atoi(find_var_value(shell->env, "SHLVL")) + 1);
	ft_setvar(&shell->env, "SHLVL", sl);
	ft_strdel(&sl);
}

void		hdl_sighup(int sig)
{
	t_cfg	*shell;
	t_list	*lst;
	t_job	*j;

	shell = cfg_shell();
	lst = shell->job;
	while (lst)
	{
		j = lst->data;
		kill(-j->pgid, sig);
		kill(-j->pgid, SIGCONT);
		lst = lst->next;
	}
	if (shell->cur_job)
		kill(-shell->cur_job, sig);
	ft_printf("\n%s:\t%d hangup\n", PROJECT, shell->pid);
	exit_routine(shell, 129);
}

static int	check_terminal(t_cfg *cfg, uint8_t tty)
{
	if (isatty(tty))
	{
		if ((tcgetattr(tty, &cfg->term_origin) == FALSE))
			ft_ex(EX);
		return (1);
	}
	ft_ex(EXFD);
	return (0);
}

void		print_ressource(char *rsc)
{
	int32_t		ret;
	int32_t		fd;
	char		*path;
	char		*ascii;

	ascii = 0;
	path = create_abs_path(rsc);
	protect_malloc(path);
	if (((fd = open(path, O_RDONLY))) == -1)
	{
		ft_strdel(&path);
		return ;
	}
	while ((ret = get_next_line(fd, &ascii)) > 0)
	{
		if (ret == -1)
			ft_ex(EXUEPTD);
		ft_printf("%s\n", ascii);\
		ft_strdel(&ascii);
	}
	ft_strdel(&path);
	ft_strdel(&ascii);
	close(fd);
}

t_cfg		*init_shell(char **env, char **av, int ac)
{
	uint8_t		shell_terminal;
	pid_t		shell_pgid;
	t_cfg		*shell;

	shell_terminal = STDIN_FILENO;
	shell = init_cfg(env, av, ac);
	if (shell->interactive && check_terminal(shell, shell_terminal))
	{
		while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
			kill(-shell_pgid, SIGTTIN);
		set_signal_ign();
		signal(SIGHUP, hdl_sighup);
		if (setpgid(shell->pid, shell->pid) < 0)
			ft_ex(EX);
		if (tcsetpgrp(shell_terminal, shell->pid))
			ft_ex(EX);
		print_ressource("ressources/42sh_header.txt");
	}
	return (shell);
}
