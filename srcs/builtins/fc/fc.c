#include "exec.h"
#include "line_edition.h"
#include "libft.h"
#include <struct.h>
#include <sh.h>
#include "ft_printf.h"
#include "get_next_line.h"
#include "var.h"

uint8_t	protect_fd(int8_t value)
{
	static uint8_t	protect = 0;

	if (value > -1)
		protect = value;
	return (protect);
}

void	del_fc_cmd(void)
{
	t_dlist	*hs;
	char	*nb;

	hs = cfg_shell()->history;
	while (hs->next)
		hs = hs->next;
	nb = ft_itoa(cfg_shell()->hist_nb);
	ft_dlstdelone(&hs);
	ft_hash_delone(cfg_shell()->hist_map, nb, free);
	cfg_shell()->hist_nb -= 1;
	ft_strdel(&nb);
}

uint8_t	ft_fc(t_process *p)
{
	int8_t	fl;
	int32_t	ac;

	ac = 1;
	if (p && (fl = fc_check_opt(p, &ac)) >= 0)
	{
		if (fl & 1 || fl & 16)
			del_fc_cmd();
		if (((!(fl & 2) && !(fl & 16)) || fl & 1)
				&& !edit_hist(&fl, p->av, ac))
			return (FAILURE);
		if (fl & 2 && !print_hist(&fl, p->av, ac))
			return (FAILURE);
		if (fl & 16)
			reexecute_cmd(p->av, ac);
		return (fl & 1 || fl & 16 ?
				ft_atoi(find_var_value(cfg_shell()->sp, "?")) : SUCCESS);
	}
	return (FAILURE);
}
