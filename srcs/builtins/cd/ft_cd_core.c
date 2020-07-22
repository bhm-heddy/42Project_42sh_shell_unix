#include "libft.h"
#include "exec.h"
#include "lexer.h"
#include "struct.h"
#include "sh.h"
#include "var.h"
#include "ft_printf.h"
#include <dirent.h>
#include <sys/stat.h>

int		cd_home(t_process *p)
{
	char	**str;
	char	*home;
	int		ret;

	home = find_var_value(p->env, "HOME");
	if (!home || !*home)
	{
		if (home && !*home)
			return (0);
		ft_dprintf(2, "%s: cd: HOME not set\n", NAME_SH);
		return (1);
	}
	home = ft_strdup(home);
	if (!(str = (char**)malloc(sizeof(char*) * 3)))
		ft_ex(EXMALLOC);
	str[0] = ft_strdup("cd");
	str[1] = home;
	str[2] = NULL;
	tabfree(p->av);
	p->av = str;
	ret = ft_cd(p);
	str = NULL;
	return (ret);
}

char	*cd_setcurpath(t_list **env, char *opr)
{
	char	*ret;
	char	**cdpath;

	if ((!ft_strncmp(opr, "./", 2) || !ft_strcmp(opr, ".")
				|| !ft_strncmp(opr, "../", 3) || !ft_strcmp(opr, "..")))
		return (ft_strdup(opr));
	ret = find_var_value(*env, "CDPATH");
	cdpath = ft_strsplit(ret, ":");
	while (cdpath && *cdpath)
	{
		ret = ft_pathjoin(*cdpath, opr);
		if (ft_isdir(ret, 1))
			break ;
		ft_strdel(&ret);
		cdpath++;
	}
	tabfree(cdpath);
	if (!ret)
		return (ft_strdup(opr));
	return (ret);
}

int		cd_set_relativepath(t_list **env, char *curpath, char *opr, char *pwd)
{
	char	*tmp;
	char	*oldpath;
	int		ret;

	oldpath = ft_strdup(curpath);
	if (ft_strlen(curpath) >= PATH_MAX && ft_strlen(opr) < PATH_MAX
			&& !ft_strncmp(curpath, pwd, ft_strlen(pwd)))
	{
		tmp = curpath[ft_strlen(pwd)] == '/' ?
			ft_strdup(curpath + ft_strlen(pwd) + 1) :
			ft_strdup(curpath + ft_strlen(pwd));
		ft_strdel(&curpath);
		curpath = tmp;
	}
	ft_strdel(&pwd);
	ret = cd_change_directory(env, curpath, opr, oldpath);
	return (ret);
}

int		cd_logically(t_list **env, char *curpath, char *opr)
{
	char	*pwd;
	char	*error;

	error = NULL;
	if (!(curpath = cd_del_dotcomponents(curpath, opr, &pwd, env)))
	{
		ft_strdel(&pwd);
		return (1);
	}
	if (check_chdir_errors(&error, curpath, opr)
			&& ft_strcmp(ft_strrchr(error, ':'), ": Not a directory\n"))
	{
		ft_strdel(&curpath);
		ft_strdel(&pwd);
		return (display_cd_errors(error));
	}
	ft_strdel(&error);
	return (cd_set_relativepath(env, curpath, opr, pwd));
}

int		cd_change_directory(t_list **env, char *curpath, char *opr, char *pwd)
{
	char	*oldpwd;
	char	*str;

	if ((str = find_var_value(*env, "PWD")))
		oldpwd = ft_strdup(str);
	else if (!(oldpwd = getcwd(NULL, 0)))
		ft_ex(EX);
	if (chdir(curpath) == -1)
		return (chdir_errors(curpath, opr, pwd, oldpwd));
	ft_strdel(&curpath);
	if (!pwd && !(pwd = getcwd(NULL, 0)))
		ft_ex(EX);
	ft_setvar(&cfg_shell()->env, "PWD", pwd);
	ft_setvar(&cfg_shell()->env, "OLDPWD", oldpwd);
	ft_strdel(&oldpwd);
	ft_strdel(&pwd);
	return (0);
}
