#include "debug.h"
#include "sh.h"
#include "libft.h"
#include "ft_printf.h"

void	field_splitting_debug(t_simple_cmd *cmd, char *str)
{
	t_list			*args;
	int				n_arg;
	int				nb_args;

	n_arg = 0;
	nb_args = 0;
	args = cmd->args;
	ft_dprintf(cfg_shell()->debug, "\nField Splitting %s,\n\n", str);
	if (args && (nb_args = get_nb_word_list(args)))
		n_arg = 1;
	if (cmd->cmd_name)
	{
		ft_dprintf(cfg_shell()->debug,
		"\t\t\033[1m-----------------\033[0m\n");
		ft_dprintf(cfg_shell()->debug, "\t\t| %13s |\n", "cmd_name");
		ft_dprintf(cfg_shell()->debug,
		"\t\t| %13s |\n", cmd->cmd_name);
		ft_dprintf(cfg_shell()->debug, "\t\t-----------------\n");
	}
	handle_args(args, n_arg, nb_args);
}
