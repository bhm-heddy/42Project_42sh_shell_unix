#include "libft.h"
#include "exec.h"
#include "sh.h"
#include "ft_printf.h"
#include "var.h"
#include "struct.h"

int8_t			protect_job(int8_t update)
{
	static int8_t	pj = 1;

	if (update > 0 && pj < 1)
		pj += update;
	else if (update < 0)
		pj += update;
	return (pj);
}

static int16_t	exit_opt(t_list *sp, char **av, uint8_t *ret)
{
	int i;

	i = -1;
	if (!av[1])
		return ((*ret = ft_atoi(find_var_value(sp, "?"))));
	while (av[1][++i])
		if ((av[1][i] < 48 || av[1][i] > 57) && av[1][i] != '-')
		{
			ft_dprintf(STDERR_FILENO,
					"%s: exit: %s: numeric argument required\n",
					PROJECT, av[1]);
			return ((*ret = 2));
		}
	if (av[2])
	{
		ft_dprintf(STDERR_FILENO, "%s: exit: too many arguments\n", PROJECT);
		return (-1);
	}
	return ((*ret = ft_atoi(av[1])));
}

uint8_t			ft_exit(t_process *p)
{
	uint8_t		ret;
	t_cfg		*shell;

	ret = 0;
	shell = cfg_shell();
	if (find_job_by_status(shell->job, STOPPED) && protect_job(0) > 0)
	{
		protect_job(-2);
		ft_dprintf(STDERR_FILENO, "You have job stopped !\n");
		return (FAILURE);
	}
	if (shell->interactive)
		ft_dprintf(STDERR_FILENO, "exit\n");
	if (exit_opt(shell->sp, p->av, &ret) == -1)
		return (1);
	exit_routine(shell, ret);
	return (0);
}
