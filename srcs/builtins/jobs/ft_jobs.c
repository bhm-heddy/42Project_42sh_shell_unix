#include "libft.h"
#include "ft_printf.h"
#include "exec.h"
#include "sh.h"

static int8_t	error(char err)
{
	ft_dprintf(STDERR_FILENO, "%s: jobs: -%c: invalid option\n%s\n",
			PROJECT, err, JOB_USG);
	return (FAILURE);
}

static char		jobs_opt(char **av, int *ac)
{
	int32_t		i;
	int8_t		ret;
	char		opt;

	i = 0;
	opt = 0;
	while ((ret = ft_getopt(ac, &i, av, "pl")) != -1)
	{
		if (ret == '?')
			return (error(av[*ac][i]));
		opt = ret != -1 ? ret : opt;
	}
	return (opt);
}

uint8_t			ft_jobs(t_process *p)
{
	int32_t		ac;
	char		opt;
	t_cfg		*shell;

	shell = cfg_shell();
	ac = 1;
	if ((opt = jobs_opt(p->av, &ac)) == FAILURE)
		return (2);
	if (p->av[ac])
		return (print_jobs(shell, p, opt, ac));
	else
		return (print_all_jobs(shell, shell->job, opt));
	return (0);
}
