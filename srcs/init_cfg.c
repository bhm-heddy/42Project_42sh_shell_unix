#include "exec.h"
#include "struct.h"
#include "libft.h"
#include "sh.h"
#include "var.h"
#include "exec.h"
#include "ft_printf.h"
#include "line_edition.h"

static void		argv_path_fail(char *path, char *mode, uint32_t err)
{
	int8_t		tmp;
	char		*taberr[5];

	tmp = 0;
	taberr[0] = STR_ISDIR;
	taberr[1] = STR_NOENT;
	taberr[2] = STR_ACCES;
	taberr[3] = STR_LOOP;
	taberr[4] = STR_NTL;
	if (!err)
		err = E_NOENT;
	err = err >> 7;
	while (!((err = err >> 1) & 1))
		tmp++;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n",
			PROJECT, mode, path, taberr[tmp]);
	exit_routine(cfg_shell(), 1);
}

static uint16_t	set_debug(char **av, int *ac)
{
	int			fd;
	uint32_t	err;

	if (!av[*ac] || *av[*ac] == '-')
		return (STDERR_FILENO);
	if ((fd = open(av[*ac], O_CREAT | O_WRONLY, 0644)) == -1)
	{
		err = check_access(av[*ac], W_OK);
		argv_path_fail(av[*ac], "Debug mode fail", err);
	}
	if (dup2(fd, FD_DEBUG) == -1)
		ft_ex(EX);
	close(fd);
	fd = FD_DEBUG;
	*ac += 1;
	return (fd);
}

static void		set_nonint(t_cfg *shell, char *path)
{
	int32_t		err;

	shell->file = (*path == '/') ? ft_strdup(path) : create_abs_path(path);
	if (((err = check_access(shell->file, R_OK))) != TRUE)
		argv_path_fail(shell->file, "Non-interactive mode fail", err);
	shell->interactive = 0;
}

static void		set_shell_mode(char **av, int ac, t_cfg *shell)
{
	int32_t		i;
	int8_t		ret;

	i = 0;
	shell->interactive = TRUE;
	if (ac == 1)
		return ;
	ac = 1;
	while ((ret = ft_getopt(&ac, &i, av, "dh")) != -1)
	{
		if (ret == '?')
		{
			ft_dprintf(STDERR_FILENO, "%s: -%c : Bad option\n%s",
					PROJECT, av[ac][i], USAGE);
			exit_routine(shell, FAILURE);
		}
		else if (ret == 'd')
			shell->debug = set_debug(av, &ac);
		else if (ret == 'h')
			print_features();
	}
	if (av[ac])
		set_nonint(shell, av[ac]);
}

t_cfg			*init_cfg(char **env, char **av, int ac)
{
	t_cfg	*shell;

	shell = cfg_shell();
	ft_bzero(shell, sizeof(t_cfg));
	shell->term_origin.c_iflag = -1;
	shell->pid = getpid();
	create_lst_var(&shell->env, env);
	set_var(shell);
	shell->history = get_history();
	shell->clipboard = NULL;
	if (!(shell->map = ft_hash_init(128))
		|| !(shell->input_map = ft_hash_init(64))
		|| !(shell->builtin_map = ft_hash_init(16)))
		ft_ex(EXMALLOC);
	init_builtin_map(shell->builtin_map);
	init_input_map(shell->input_map);
	init_test_op();
	set_shell_mode(av, ac, shell);
	return (shell);
}
