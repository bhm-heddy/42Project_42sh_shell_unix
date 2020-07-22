#include "libft.h"
#include "struct.h"
#include "var.h"
#include "sh.h"
#include "ft_printf.h"
#include "exec.h"
#include "job_control.h"

t_list			*find_job_by_status(t_list *lst, uint8_t want)
{
	t_job	*j;

	while (lst)
	{
		j = lst->data;
		if (j->status == want)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void			insert_running_job(t_cfg *shell, t_list *ljob, t_job *jc)
{
	t_job	*j;
	t_list	*tmp;
	t_list	*new;

	if (!shell->job || ((t_job *)(shell->job->data))->status & RUNNING)
		ft_lst_push_front(&shell->job, jc, sizeof(t_job));
	else
	{
		j = ljob->data;
		new = ft_lstnew(jc, sizeof(t_job));
		protect_malloc(new);
		tmp = ljob;
		while (ljob && (j->status & STOPPED))
		{
			tmp = ljob;
			ljob = ljob->next;
		}
		tmp->next = new;
		new->next = ljob;
	}
}

void			set_job_background(t_job *job)
{
	add_job_cfg(job);
	ft_printf("[%d] %d\n", job->id, job->pgid);
}

void			cpy_lst_process(void *copy, void *process)
{
	t_process *p;
	t_process *c;

	p = process;
	c = copy;
	ft_bzero(c, sizeof(t_process));
	c->cmd = ft_strdup(p->cmd);
	c->av = ft_tabdup(p->av);
	c->path = ft_strdup(p->path);
	c->status = p->status;
	c->setup = p->setup;
	c->pid = p->pid;
	c->ret = p->ret;
}
