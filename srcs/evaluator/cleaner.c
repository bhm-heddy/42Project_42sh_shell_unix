#include "exec.h"
#include "libft.h"
#include "sh.h"

void	free_fd(void *del, size_t u)
{
	(void)u;
	free(del);
}

void	del_struct_process(void *del, size_t u)
{
	t_process *p;

	(void)u;
	p = del;
	ft_lstdel(&p->env, del_struct_tvar);
	ft_lstdel(&p->fd, free_fd);
	ft_strdel(&(p->cmd));
	ft_del_tab((void **)p->av);
	ft_strdel(&p->path);
	ft_strdel(&p->message);
	free(del);
}

void	routine_clean_job(void *del, size_t u)
{
	t_job	*j;

	j = del;
	ft_strdel(&j->cmd);
	ft_lstdel(&j->process, del_struct_process);
	ft_bzero(j, u);
}

void	del_struct_job(void *del, size_t u)
{
	routine_clean_job(del, u);
	free(del);
}
