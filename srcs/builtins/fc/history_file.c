#include "exec.h"
#include "line_edition.h"
#include "libft.h"
#include <struct.h>
#include <sh.h>
#include "ft_printf.h"
#include "get_next_line.h"
#include "var.h"

char	*get_histfilename(void)
{
	char	*name;
	char	*tmp;
	char	*prefix;
	int		i;

	prefix = "/tmp";
	name = "/edit_hist";
	if (access(prefix, W_OK | R_OK) < 0)
		prefix = ".";
	if (access(prefix, W_OK | R_OK) < 0)
		return (NULL);
	i = 0;
	ft_asprintf(&name, "%s%s", prefix, name);
	prefix = ft_strdup(name);
	while (access(prefix, F_OK) != -1 || i == 0)
	{
		ft_strdel(&prefix);
		i++;
		tmp = ft_itoa(i);
		ft_asprintf(&prefix, "%s_%s", name, tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(&name);
	name = prefix;
	return (name);
}

char	*create_tmphist(int8_t *fl, char **av, int ac)
{
	t_point range;
	char	*file;
	int		fd;
	int		order;
	char	*key;

	file = get_histfilename();
	if (!file || (fd = open(file, O_CREAT | O_RDONLY | O_WRONLY, 0666)) < 0)
		return (NULL);
	range = get_range(fl, av, ac, cfg_shell());
	if (*fl & 8)
		range = (t_point){range.y, range.x};
	order = (range.x > range.y ? -1 : 1);
	while (range.x - order != range.y && range.x > 0)
	{
		key = ft_itoa(range.x);
		ft_putstr_fd((char *)ft_hash_lookup(cfg_shell()->hist_map, key), fd);
		ft_putstr_fd("\n", fd);
		ft_strdel(&key);
		range.x += order;
	}
	close(fd);
	return (file);
}
