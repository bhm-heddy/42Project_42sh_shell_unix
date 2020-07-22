#include "libft.h"
#include "exec.h"
#include "var.h"
#include "sh.h"
#include "ft_printf.h"

uint32_t	redir_gear(t_process *p, t_redir *r, uint32_t target,
		uint32_t right)
{
	int32_t		source;
	int32_t		error;
	char		*path;

	path = NULL;
	if ((error = path_gearing(r, &path, right)))
		return (redir_errors_handling(p, error, path, 0));
	if ((error = right_fifo(path, &right)))
		return (redir_errors_handling(p, error, path, 0));
	if ((source = open(path, right, 0644)) == -1)
		ft_ex(EXUEPTD);
	if (bad_fd(target))
	{
		do_my_dup2(source, target);
		close(source);
		source = target;
	}
	add_fd_process(&p->fd, source, target);
	ft_strdel(&path);
	return (SUCCESS);
}

uint32_t	redir_file(t_process *p, t_redir *r)
{
	uint32_t	target;
	uint32_t	right;
	uint8_t		io;

	io = (r->type == GREAT || r->type == DGREAT) ? 1 : 0;
	right = (io == 1) ? (O_WRONLY | O_CREAT) : O_RDONLY;
	target = (*r->io_num) ? ft_atoi(r->io_num) : io;
	if (target > 255)
		return (redir_errors_handling(p, E_BADFD, 0, target));
	if (r->type == GREAT)
		right |= O_TRUNC;
	else if (r->type == DGREAT)
		right |= O_APPEND;
	return (redir_gear(p, r, target, right));
}

uint32_t	redir_fd(t_process *p, t_redir *r)
{
	uint8_t		io;
	int32_t		target;
	int32_t		source;
	int32_t		tmp;

	io = (r->type == LESSAND) ? 0 : 1;
	target = (*r->io_num) ? ft_atoi(r->io_num) : io;
	source = (*r->file == '-') ? -1 : ft_atoi(r->file);
	if (source == -1)
		return (add_fd_process(&p->fd, source, target));
	if (target > 255)
		return (redir_errors_handling(p, E_BADFD, 0, target));
	if (bad_fd(source))
		return (redir_errors_handling(p, E_BADFD, 0, source));
	if (bad_fd(target))
	{
		if (!(tmp = create_fd_null()))
			return (redir_errors_handling(p, E_BADFD, 0, target));
		if (tmp != target)
		{
			do_my_dup2(tmp, target);
			close(tmp);
		}
	}
	return (add_fd_process(&p->fd, source, target));
}

uint32_t	redir_heredoc(t_process *p, t_redir *r)
{
	int32_t		fd;
	char		*path;

	path = NULL;
	ft_asprintf(&path, "/tmp/%s-heredoc-%p", PROJECT, r);
	protect_malloc(path);
	if (((fd = open(path, O_CREAT | O_WRONLY, 0644)) == -1))
		ft_ex(EXUEPTD);
	if (write(fd, r->file, ft_strlen(r->file)) == -1)
		ft_ex(EXUEPTD);
	close(fd);
	ft_strdel(&r->file);
	r->file = path;
	return (redir_file(p, r));
}

uint32_t	process_redir(t_process *p, t_list *redir)
{
	uint32_t	error;
	t_redir		*r;

	while (redir)
	{
		r = redir->data;
		if (!r->file && !(r->type == DLESS || r->type == DLESSDASH))
			ft_ex(EXUEPTD);
		if (r->type == DLESS || r->type == DLESSDASH)
			error = redir_heredoc(p, r);
		else if (r->type != LESSAND && r->type != GREATAND)
			error = redir_file(p, r);
		else
			error = redir_fd(p, r);
		if (error)
			return (error);
		redir = redir->next;
	}
	return (SUCCESS);
}
