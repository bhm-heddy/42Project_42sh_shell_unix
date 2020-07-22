#include "libft.h"
#include "ft_printf.h"
#include "exec.h"
#include "sh.h"
#include <sys/stat.h>

char		*create_abs_path(char *s)
{
	char		*buf;
	char		*tmp;

	if (!(buf = getcwd(0, 0)))
		ft_ex(EX);
	ft_asprintf(&tmp, "%s/%s", buf, s);
	ft_strdel(&buf);
	return (tmp);
}

uint8_t		c_isdir(char *path)
{
	struct stat		buf;

	if (lstat(path, &buf) == SUCCESS)
		if ((S_IFDIR == (S_IFMT & buf.st_mode)))
			return (1);
	return (0);
}

char		*remove_file_name(char *s)
{
	int		i;
	char	*dst;

	dst = ft_strdup(s);
	i = ft_strrchri(dst, '/');
	dst[i + 1] = '\0';
	return (dst);
}

int8_t		check_right(char *path, int right)
{
	if (access(path, right))
		return (FALSE);
	return (SUCCESS);
}

uint32_t	check_access(char *path, int right)
{
	char		*tmp;
	uint32_t	ret;

	ret = SUCCESS;
	tmp = NULL;
	if (access(path, F_OK) == SUCCESS)
	{
		if (c_isdir(path))
			return (E_ISDIR);
		if (check_right(path, right))
			return (E_ACCES);
		return (TRUE);
	}
	tmp = remove_file_name(path);
	if (access(tmp, F_OK))
		ret = E_NOENT;
	else if (access(tmp, X_OK | W_OK))
		ret = E_ACCES;
	ft_strdel(&tmp);
	return (ret);
}
