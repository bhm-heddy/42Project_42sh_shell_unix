#include "libft.h"
#include "ft_printf.h"
#include "sh.h"
#include "get_next_line.h"
#include "var.h"
#include "line_edition.h"
#include "struct.h"
#include <stdlib.h>

int		ft_strcheck(char *s, char *oc)
{
	int	i;

	if (s && oc)
	{
		i = 0;
		while (s[i])
			if (!ft_strchr(oc, s[i++]) && s[i - 1] != '\n')
				return (0);
		return (1);
	}
	return (0);
}

char	*get_home(void)
{
	t_cfg	*cfg;
	char	*home;

	if ((cfg = cfg_shell()))
		if ((home = find_var_value(cfg->env, "HOME")))
			return (home);
	return (".");
}

int		open_histfd(void)
{
	char	*path;
	int		fd;

	path = NULL;
	ft_asprintf(&path, "%s/.%s_history", get_home(), PROJECT);
	fd = open(path, O_CREAT | O_APPEND | O_WRONLY, 0666);
	ft_strdel(&path);
	return (fd);
}
