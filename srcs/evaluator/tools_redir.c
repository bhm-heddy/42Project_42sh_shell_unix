#include "libft.h"
#include "ft_printf.h"
#include "exec.h"
#include "sh.h"

uint8_t		add_fd_process(t_list **fd, int16_t source, int16_t target)
{
	int16_t		tab[2];

	tab[0] = source;
	tab[1] = target;
	ft_lst_push_back(fd, tab, sizeof(tab));
	return (SUCCESS);
}

void		do_my_dup2(int16_t fd1, int16_t fd2)
{
	char	*err;

	if (fd1 == -1)
		return ;
	if (dup2(fd1, fd2) == -1)
	{
		ft_asprintf(&err, "%d: %s", fd1, EXFD2);
		protect_malloc(err);
		ft_ex(err);
	}
}

void		do_redir(t_list *fd)
{
	int16_t *t;

	while (fd)
	{
		t = fd->data;
		if (t[0] == -1)
			close(t[1]);
		else if (t[0] != t[1])
			do_my_dup2(t[0], t[1]);
		fd = fd->next;
	}
}

void		do_pipe(t_process *p)
{
	if (p->std[0] != STDIN_FILENO &&
			p->std[0] != -1)
	{
		do_my_dup2(p->std[0], STDIN_FILENO);
		close(p->std[0]);
	}
	if (p->std[1] != STDOUT_FILENO &&
			p->std[1] != -1)
	{
		do_my_dup2(p->std[1], STDOUT_FILENO);
		close(p->std[1]);
	}
}

uint32_t	path_gearing(t_redir *r, char **path, int right)
{
	int32_t		exist;
	int32_t		r_or_w;

	r_or_w = (right & O_WRONLY) ? W_OK : R_OK;
	*path = (*r->file == '/') ? ft_strdup(r->file) : create_abs_path(r->file);
	if (((exist = check_access(*path, r_or_w)) & (E_ACCES | E_NOENT | E_ISDIR)))
		return (exist);
	if (r->type == LESS && !exist)
		return (E_NOENT);
	return (SUCCESS);
}
