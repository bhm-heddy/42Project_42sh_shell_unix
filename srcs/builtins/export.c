#include "libft.h"
#include "ft_printf.h"
#include "exec.h"
#include "var.h"
#include "sh.h"

static int8_t		export_error(char err)
{
	char	*usage;

	usage = "export: usage: export [name[=value] ...] or export -p";
	ft_dprintf(STDERR_FILENO, "%s: export: -%c: invalid option\n%s\n",
			PROJECT, err, usage);
	return (-1);
}

static void			just_export(t_cfg *shell, char *name)
{
	char	*value;

	if ((value = find_var_value(shell->intern, name)))
	{
		ft_setvar(&shell->env, name, value);
		ft_lstdelif(&shell->intern, name, unsetvar_find, unsetvar_del);
	}
}

static void			new_or_update(t_cfg *shell, char *input, char *equal)
{
	*equal = '\0';
	ft_lstdelif(&shell->intern, input, unsetvar_find, unsetvar_del);
	ft_setvar(&shell->env, input, equal + 1);
	*equal = '=';
}

static uint8_t		check_opt(t_process *p, int32_t *ac)
{
	int8_t		ret;
	uint8_t		opt;
	int32_t		i;

	i = 0;
	opt = 0;
	while ((ret = ft_getopt(ac, &i, p->av, "p")) != -1)
	{
		if (ret == '?')
			return (export_error(p->av[*ac][i]));
		if (ret == 'p')
			opt = TRUE;
	}
	if (!p->av[*ac])
		opt = TRUE;
	return (opt);
}

uint8_t				ft_export(t_process *p)
{
	int32_t		ac;
	int8_t		ret;
	t_cfg		*shell;
	char		*equal;

	ac = 1;
	shell = cfg_shell();
	if ((ret = check_opt(p, &ac)) > 0)
		return (ft_print_var_lst(shell->env, 1));
	if (ret == -1)
		return (FAILURE);
	while (p->av[ac])
	{
		if ((equal = ft_strchr(p->av[ac], '=')))
			new_or_update(shell, p->av[ac], equal);
		else
			just_export(shell, p->av[ac]);
		ac++;
	}
	return (SUCCESS);
}
