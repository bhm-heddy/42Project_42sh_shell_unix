#include "exec.h"
#include "libft.h"
#include "sh.h"
#include "var.h"
#include <unistd.h>

static void		assign_for_currenv(t_cfg *shell, t_list *assignment)
{
	t_list			*tmp;
	t_assignment	*assign;

	while (assignment)
	{
		assign = assignment->data;
		if (!ft_strcmp(assign->var, "PS1"))
			build_prompt_ps1(1);
		if ((tmp = find_var(shell->env, assign->var)))
			ft_setvar(&tmp, assign->var, assign->val);
		else
			ft_setvar(&shell->intern, assign->var, assign->val);
		assignment = assignment->next;
	}
}

static void		assign_for_b_special(t_cfg *shell, t_list *assignment)
{
	t_assignment	*assign;

	while (assignment)
	{
		assign = assignment->data;
		ft_lstdelif(&shell->intern, assign->var, unsetvar_find, unsetvar_del);
		ft_setvar(&shell->env, assign->var, assign->val);
		assignment = assignment->next;
	}
}

void			process_assign(t_cfg *shell, t_process *p, t_list *assignment)
{
	t_assignment	*assign;

	if (!assignment)
		return ;
	if (p->setup & NOCMD && !(p->setup & PIPE_ON))
		assign_for_currenv(shell, assignment);
	else if (p->setup & B_SPECIAL && !(p->setup & PIPE_ON))
		assign_for_b_special(shell, assignment);
	else
	{
		while (assignment)
		{
			assign = assignment->data;
			ft_setvar(&p->env, assign->var, assign->val);
			assignment = assignment->next;
		}
	}
}
