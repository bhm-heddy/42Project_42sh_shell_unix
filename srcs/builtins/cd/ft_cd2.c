#include "libft.h"
#include "exec.h"
#include "struct.h"
#include "sh.h"
#include "var.h"
#include "ft_printf.h"
#include <dirent.h>
#include <sys/stat.h>

char			cd_getopt(char **str, int *i)
{
	char	opt;
	int		a;

	opt = 'L';
	a = *i;
	while (str[a] && str[a][0] == '-' && str[a][1])
	{
		if (str[a][1] == 'P' || str[a][1] == 'L')
			opt = str[a][1];
		else if (str[a][1] != '-' || (str[a][1] == '-' && str[a][2]))
		{
			ft_dprintf(2, "%s: cd: -%c: invalid option\n",
			PROJECT, str[a][1]);
			ft_dprintf(2, "Usage: cd [-L|-P] [dir]\n");
			return (0);
		}
		if (str[a][1] == '-')
			break ;
		a++;
	}
	*i = a;
	return (opt);
}

static char		*ft_del_dots(char *curpath)
{
	char	*res;
	size_t	clen;

	if (!curpath)
		return (NULL);
	clen = ft_strlen(curpath);
	if (!clen)
		res = ft_strdup(".");
	if (curpath[clen - 1] == '/' && clen > 1)
		curpath[clen - 1] = 0;
	if (clen > 2 && curpath[clen - 1] == '.' && curpath[clen - 2] == '/')
	{
		curpath[clen - 2] = '\0';
		res = ft_strdup(curpath);
	}
	else if (ft_strequ(curpath, "/."))
		res = ft_strdup("/");
	else if (ft_strstr(curpath, "/./"))
		res = ft_strrep(curpath, "/./", "/");
	else
		return (curpath);
	ft_strdel(&curpath);
	return (ft_del_dots(res));
}

static char		*ft_del_dotdots2(char *curpath, int i)
{
	char	*res;
	char	*tmp;
	char	*tmp2;
	size_t	res_len;

	if (!ft_strncmp(curpath, "/..", 3))
		return (ft_strrep(curpath, "..", NULL));
	if (!(tmp = ft_strdup(curpath)))
		return (0);
	tmp[i - 1] = '\0';
	tmp2 = ft_strrchr(tmp, '/');
	tmp2 = tmp2 ? tmp2 + 1 : tmp2;
	tmp[i - 1] = '/';
	if (tmp[i + 2])
		tmp[i + 3] = '\0';
	res = ft_strrep(curpath, tmp2, NULL);
	res_len = ft_strlen(res);
	if (res_len > 1 && res[res_len - 1] == '/')
		res[res_len - 1] = '\0';
	free(tmp);
	return (res);
}

static char		*ft_del_dotdots(char *curpath, char *opr)
{
	int		i;
	char	*res;

	i = -1;
	res = NULL;
	if (!curpath)
		return (0);
	while (curpath[++i])
	{
		if (curpath[i] == '.' && curpath[i + 1] == '.' && i >= 1
		&& curpath[i - 1] == '/' && (!curpath[i + 2] || curpath[i + 2] == '/')
		&& !((i == 3 || (i > 3 && curpath[i - 4] == '/'))
		&& curpath[i - 3] == '.' && curpath[i - 2] == '.'))
		{
			res = ft_del_dotdots2(curpath, i);
			free(curpath);
			return (ft_del_dotdots(res, opr));
		}
	}
	return (curpath);
}

char			*cd_del_dotcomponents(char *curpath,
char *opr, char **pwd, t_list **env)
{
	char	*tmp;

	if (!(*pwd = ft_strdup(find_var_value(*env, "PWD"))))
		if (!(*pwd = getcwd(NULL, 0)))
			ft_ex(EXMALLOC);
	if (!ft_strchr(*pwd, '/'))
	{
		ft_strdel(pwd);
		if (!(*pwd = getcwd(NULL, 0)))
			ft_ex(EXMALLOC);
	}
	if (*curpath != '/')
	{
		tmp = curpath;
		curpath = ft_pathjoin(*pwd, curpath);
		ft_strdel(&tmp);
	}
	if (!(curpath = ft_del_dots(curpath)))
		ft_ex(EXMALLOC);
	if (!(curpath = ft_del_dotdots(curpath, opr)))
		ft_ex(EXMALLOC);
	return (curpath);
}
