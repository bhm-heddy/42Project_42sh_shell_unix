#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "var.h"
#include "sh.h"
#include "exec.h"

static int			check_alias_name(char *name)
{
	int		i;

	i = 0;
	if (!name[i])
	{
		ft_dprintf(2, "%s: alias: %s : Invalid alias name\n",
		PROJECT, name);
		return (0);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) || ft_strchr("=-/_!%,@", name[i]))
		{
			ft_dprintf(2, "%s: alias: %s : Invalid alias name\n",
			PROJECT, name);
			return (0);
		}
		i++;
	}
	return (1);
}

static	uint8_t		add_alias(char *name, char *value)
{
	t_var	*var;

	if ((var = search_alias_var(name, cfg_shell()->alias)))
	{
		ft_strdel(&var->ctab[1]);
		if (!(var->ctab[1] = ft_strdup(value)))
			ft_ex(EXMALLOC);
	}
	else
		setvar_add(&cfg_shell()->alias, name, value);
	ft_strdel(&name);
	ft_strdel(&value);
	return (1);
}

static	uint8_t		make_alias(char *assign)
{
	char	*name;
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	if ((tmp = ft_strchr(assign, '=')))
	{
		if (!(name = ft_strsub(assign, 0, tmp - assign)))
			ft_ex(EXMALLOC);
		if (!(value = ft_strdup(tmp + 1)))
			ft_ex(EXMALLOC);
	}
	else
		return (0);
	if (check_alias_name(name))
		return (add_alias(name, value));
	ft_strdel(&name);
	ft_strdel(&value);
	return (0);
}

uint8_t				ft_alias(t_process *p)
{
	int	i;

	i = 1;
	if (!p->av || !p->av[1])
		print_all_alias();
	else
		while (p->av[i])
		{
			if (ft_strchr(p->av[i], '='))
			{
				if (!make_alias(p->av[i]))
					return (1);
			}
			else if (!print_single_alias(p->av[i]))
				return (1);
			i++;
		}
	return (0);
}
