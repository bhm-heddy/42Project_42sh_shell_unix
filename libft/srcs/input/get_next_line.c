#include "get_next_line.h"
#include "libft.h"

static int			ft_return(char *tmp, char **buff, char **line)
{
	char			*n;

	if ((n = ft_strstr(tmp, "\n")))
	{
		*buff = ft_strcpy(*buff, n + 1);
		*n = '\0';
	}
	*line = tmp;
	if ((*line)[0] || n)
		return (1);
	free(*buff);
	ft_strdel(line);
	*buff = NULL;
	return (0);
}

static	t_gnl		*ft_lst_fresh(int fd)
{
	t_gnl			*new;

	if (!(new = (t_gnl *)ft_memalloc(sizeof(t_gnl))))
		return (NULL);
	if (!(new->content = (char**)malloc(sizeof(char*))))
		return (NULL);
	*(new->content) = NULL;
	new->num = fd;
	new->next = NULL;
	return (new);
}

static char			**ft_find_str(int fd)
{
	static t_gnl	*buff = NULL;
	t_gnl			*tmp;

	if (buff)
	{
		tmp = buff;
		while (tmp->next && tmp->num != fd)
			tmp = tmp->next;
		if (tmp->num != fd)
		{
			if (!(tmp->next = ft_lst_fresh(fd)))
				return (NULL);
			tmp = tmp->next;
		}
	}
	else
	{
		if (!(buff = ft_lst_fresh(fd)))
			return (NULL);
		tmp = buff;
	}
	return (tmp->content);
}

int					get_next_line(const int fd, char **line)
{
	int				res;
	char			*tmp;
	char			*n;
	char			**buff;

	if (fd >= 0 && (buff = ft_find_str(fd)) && !*buff)
		if (!(*buff = ft_strnew(BUFF_SIZE)))
			return (-1);
	if (fd < 0 || !line || !(tmp = ft_strdup(*buff))
			|| read(fd, *buff, 0) < 0)
		return (-1);
	ft_bzero(*buff, BUFF_SIZE);
	if ((n = ft_strstr(tmp, "\n")))
		return (ft_return(tmp, buff, line));
	while ((res = read(fd, *buff, BUFF_SIZE) > 0))
	{
		n = tmp;
		if (!(tmp = ft_strjoin(tmp, *buff)))
			return (-1);
		free(n);
		ft_bzero(*buff, BUFF_SIZE);
		if ((n = ft_strstr(tmp, "\n")))
			break ;
	}
	return (ft_return(tmp, buff, line));
}
