#include "libft.h"
#include "exec.h"
#include "sh.h"
#include "var.h"
#include "ft_printf.h"

uint8_t			ft_set(t_process *p)
{
	t_cfg	*shell;

	shell = cfg_shell();
	if (p->av[1])
		return (SUCCESS);
	ft_print_var_lst(shell->env, 0);
	ft_print_var_lst(shell->intern, 0);
	return (SUCCESS);
}
