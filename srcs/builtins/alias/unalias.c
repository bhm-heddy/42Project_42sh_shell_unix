#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "var.h"
#include "sh.h"
#include "exec.h"

uint8_t		ft_unalias(t_process *p)
{
	t_list	**list;
	int		i;

	list = &cfg_shell()->alias;
	i = 1;
	if (ft_strequ(p->av[1], "-a"))
	{
		ft_lstdel(&cfg_shell()->alias, unsetvar_del);
		return (0);
	}
	while (p->av[i])
	{
		if (search_alias_var(p->av[i], cfg_shell()->alias))
			ft_lstdelif(&cfg_shell()->alias, p->av[i],
			unsetvar_find, unsetvar_del);
		else
		{
			ft_dprintf(2, "%s: unalias: %s : Not found\n",
			PROJECT, p->av[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
