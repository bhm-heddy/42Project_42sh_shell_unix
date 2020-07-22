#include "libft.h"
#include <sys/stat.h>

int		ft_isdir(char *path, int link)
{
	struct stat info;

	if (!link)
		lstat(path, &info);
	else
		stat(path, &info);
	return (S_ISDIR(info.st_mode));
}
