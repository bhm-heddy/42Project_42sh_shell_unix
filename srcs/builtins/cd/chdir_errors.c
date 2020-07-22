#include "libft.h"
#include "exec.h"
#include "struct.h"
#include "sh.h"
#include "var.h"
#include "ft_printf.h"
#include <dirent.h>
#include <sys/stat.h>

int			display_cd_errors(char *error)
{
	if (!(error))
		ft_ex(EXMALLOC);
	ft_dprintf(2, "%s: cd: %s", PROJECT, error);
	free(error);
	return (1);
}

int			check_enotdir(char *path)
{
	struct stat		buf;

	if (!lstat(path, &buf))
	{
		if (!(S_IFDIR == (S_IFMT & buf.st_mode)))
		{
			if ((S_IFLNK == (S_IFMT & buf.st_mode) && !stat(path, &buf)
				&& !(S_IFDIR == (S_IFMT & buf.st_mode)))
				|| !(S_IFDIR == (S_IFMT & buf.st_mode)))
				return (0);
		}
	}
	return (1);
}

int			check_whole_path(char *path)
{
	char			*idx;
	int				ret;

	idx = path;
	ret = 0;
	while (1)
	{
		if ((idx = ft_strchr(idx, '/')))
			*idx = '\0';
		if (!ret && !c_enoent(path))
			ret = 1;
		if (!ret && !c_eloop(path))
			ret = 2;
		if (!ret && !check_enotdir(path))
			ret = 3;
		if (!ret && !c_eacces(path, S_IXUSR))
			ret = 4;
		if (idx)
			*(idx) = '/';
		if (!idx || ret)
			return (ret);
		idx++;
	}
}

int			check_chdir_errors(char **error, char *path, char *opr)
{
	char	*taberr[5];
	int		ret;

	taberr[0] = STR_NTL;
	taberr[1] = STR_NOENT;
	taberr[2] = STR_LOOP;
	taberr[3] = STR_ISNDIR;
	taberr[4] = STR_ACCES;
	ret = 0;
	if (!c_enametoolong(path))
	{
		ft_asprintf(error, "%s: %s\n", opr, taberr[ret]);
		return (FAILURE);
	}
	else if ((ret = check_whole_path(path)))
	{
		ft_asprintf(error, "%s: %s\n", opr, taberr[ret]);
		return (FAILURE);
	}
	return (SUCCESS);
}

int			chdir_errors(char *curpath, char *opr, char *pwd, char *oldpwd)
{
	char	*error;

	error = NULL;
	check_chdir_errors(&error, curpath, opr);
	ft_strdel(&oldpwd);
	ft_strdel(&pwd);
	ft_strdel(&curpath);
	if (!error)
		ft_asprintf(&error, "%s: %s\n", opr, STR_ACCES);
	return (display_cd_errors(error));
}
