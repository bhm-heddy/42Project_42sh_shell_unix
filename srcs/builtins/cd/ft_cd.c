#include "libft.h"
#include "exec.h"
#include "lexer.h"
#include "struct.h"
#include "sh.h"
#include "var.h"
#include "ft_printf.h"
#include <dirent.h>
#include <sys/stat.h>

int				cd_oldpwd(t_process *p)
{
	char	**str;
	char	*oldpwd;
	int		ret;

	oldpwd = find_var_value(p->env, "OLDPWD");
	if (!oldpwd || !*oldpwd)
	{
		ft_dprintf(2, "%s: cd: OLDPWD not set\n", PROJECT);
		return (1);
	}
	if (!(str = (char**)malloc(sizeof(char*) * 3)))
		ft_ex(EXMALLOC);
	str[0] = ft_strdup("cd");
	str[1] = ft_strdup(oldpwd);
	str[2] = NULL;
	tabfree(p->av);
	p->av = str;
	if (!(ret = ft_cd(p)))
		ft_printf("%s\n", oldpwd);
	return (ret);
}

static uint8_t	cd_too_many_args(void)
{
	ft_dprintf(2, "%s: cd: too many arguments\n", PROJECT);
	return (1);
}

uint8_t			ft_cd(t_process *p)
{
	char	opt;
	char	*opr;
	char	*curpath;
	int		i;

	i = 1;
	if (!(opt = cd_getopt(p->av, &i)))
		return (1);
	if (p->av[i] && p->av[i + 1])
		return (cd_too_many_args());
	opr = p->av[i];
	if (!opr)
		return (cd_home(p));
	else if (ft_strequ(opr, "-"))
		return (cd_oldpwd(p));
	if (!(curpath = cd_setcurpath(&p->env, opr)))
		ft_ex(EXMALLOC);
	if (opt == 'L')
		return (cd_logically(&p->env, curpath, opr));
	return (cd_change_directory(&p->env, curpath, opr, NULL));
}
