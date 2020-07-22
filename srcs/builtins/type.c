#include "libft.h"
#include "exec.h"
#include "sh.h"
#include "var.h"
#include "ft_printf.h"

static	uint8_t	type_error(char *p)
{
	ft_dprintf(STDERR_FILENO, "%s: type: %s : not found\n", PROJECT, p);
	return (FAILURE);
}

static uint8_t	type_success(t_process *p, uint8_t model)
{
	if (!model)
		ft_printf("%s is %s\n", p->cmd, p->path);
	else if (model == 1)
		ft_printf("%s is a shell builtin\n", p->cmd);
	else if (model == 2)
		ft_printf("%s is hashed (%s)\n", p->cmd, p->path);
	return (SUCCESS);
}

static uint8_t	type_find(t_cfg *shell, t_process *ptype, t_list *env)
{
	uint32_t	err;

	err = 0;
	if (ft_strchr(ptype->cmd, '/'))
	{
		with_slash(ptype, &err);
		if (!(err))
			return (type_success(ptype, 0));
		else
			return (type_error(ptype->cmd));
	}
	else if (builtin_search(shell, ptype))
		return (type_success(ptype, 1));
	else if ((ptype->path = ft_strdup(ft_hash_lookup(shell->map, ptype->cmd)))
			&& !(ERROR & path_errors(ptype->path, 1, S_IXUSR)))
		return (type_success(ptype, 2));
	else if ((ptype->path = ft_which(find_var_value(env, "PATH"), ptype->cmd))
			&& !(ERROR & path_errors(ptype->path, 1, S_IXUSR)))
		return (type_success(ptype, 0));
	else
		return (type_error(ptype->cmd));
}

uint8_t			ft_type(t_process *p)
{
	uint8_t		i;
	t_process	ptype;
	t_cfg		*shell;
	uint8_t		ret;

	i = 1;
	ret = 0;
	shell = cfg_shell();
	while (p->av[i])
	{
		ft_bzero(&ptype, sizeof(t_process));
		ptype.cmd = p->av[i];
		if (type_find(shell, &ptype, p->env) == FAILURE)
			ret = 1;
		ft_strdel(&ptype.path);
		i++;
	}
	return (ret);
}
