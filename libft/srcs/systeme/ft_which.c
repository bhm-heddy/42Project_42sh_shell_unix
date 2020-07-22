#include "libft.h"
#include "ft_printf.h"
#include <dirent.h>

char			*ft_which(char *paths, char *exec)
{
	struct dirent	*file;
	char			**tab;
	char			*tmp;
	DIR				*dir;
	int				i;

	i = -1;
	tmp = NULL;
	if (!(paths && exec && (tab = ft_strsplit(paths, ":"))))
		return (NULL);
	while (tab[++i])
	{
		if (!(dir = opendir(tab[i])))
			continue;
		while ((file = readdir(dir)))
			if (ft_strcmp(file->d_name, exec) == 0)
				break ;
		closedir(dir);
		if (file && ft_asprintf(&tmp, "%s/%s", tab[i], exec))
			break ;
	}
	ft_del_tab((void **)tab);
	return (tmp);
}
