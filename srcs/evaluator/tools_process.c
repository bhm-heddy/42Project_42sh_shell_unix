#include "libft.h"
#include "exec.h"

t_process	*find_process_by_pid(t_list *lst, pid_t child)
{
	t_process *p;

	while (lst)
	{
		p = lst->data;
		if (p->pid == child)
			return (p);
		lst = lst->next;
	}
	return (NULL);
}

t_process	*find_process_by_status(t_list *lst, uint8_t want)
{
	t_process *p;

	while (lst)
	{
		p = lst->data;
		if (p->status & want)
			return (p);
		lst = lst->next;
	}
	return (NULL);
}

uint8_t		builtin_process(t_process *p)
{
	uint8_t		(*tab_f[16])(t_process *);

	tab_f[0] = ft_echo;
	tab_f[1] = ft_cd;
	tab_f[2] = 0;
	tab_f[3] = ft_set;
	tab_f[4] = ft_unset;
	tab_f[5] = ft_hash;
	tab_f[6] = ft_exit;
	tab_f[7] = ft_jobs;
	tab_f[8] = ft_fg;
	tab_f[9] = ft_bg;
	tab_f[10] = ft_type;
	tab_f[11] = ft_export;
	tab_f[12] = ft_alias;
	tab_f[13] = ft_unalias;
	tab_f[14] = ft_test;
	tab_f[15] = ft_fc;
	if (p->status == FAILED)
		return (p->ret);
	if ((p->ret = tab_f[(p->setup >> 14)](p)))
		p->status = FAILED;
	else
		p->status = COMPLETED;
	return (p->ret);
}

void		process_type(t_process *p)
{
	uint32_t	err;

	err = 0;
	if (ft_strchr(p->cmd, '/'))
		with_slash(p, &err);
	else
		(any_slash(p->env, p, &err));
	if (err && (p->setup & R_ERROR))
		p->setup |= P_ERROR;
	else if (err)
		p->setup |= process_errors_handling(p, err);
}
