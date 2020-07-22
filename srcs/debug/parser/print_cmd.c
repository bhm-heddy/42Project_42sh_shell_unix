#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "sh.h"
#include "debug.h"

static void	handle_redir(t_simple_cmd *cmd)
{
	if (cmd->redir)
	{
		if (cmd->cmd_name || cmd->assign)
			ft_dprintf(cfg_shell()->debug, "\n");
		ft_dprintf(cfg_shell()->debug,
		"\t\t---------------------------------\n");
		ft_dprintf(cfg_shell()->debug,
		"\t\t| %7s | %6s | %10s |\n", "io_nbr", "type", "file");
		ft_lstiter(cmd->redir, print_redir);
		ft_dprintf(cfg_shell()->debug,
		"\t\t---------------------------------\n");
	}
}

static void	handle_assign(t_simple_cmd *cmd)
{
	if (cmd->assign)
	{
		if (cmd->cmd_name)
			ft_dprintf(cfg_shell()->debug, "\n");
		ft_dprintf(cfg_shell()->debug,
		"\t\t---------------------------------\n");
		ft_dprintf(cfg_shell()->debug, "\t\t| %13s | %13s |\n",
		"assign_var", "assign_val");
		ft_lstiter(cmd->assign, print_assignment);
		ft_dprintf(cfg_shell()->debug,
		"\t\t---------------------------------\n");
	}
}

void		handle_args(t_list *args, int n_arg, int nb_args)
{
	if (args)
	{
		ft_dprintf(cfg_shell()->debug, "\t\t| %13s |\n", "arguments");
		while (n_arg <= nb_args)
		{
			ft_dprintf(cfg_shell()->debug,
			"\t\t| %2d %10.10s |\n", n_arg, (char *)args->data);
			n_arg++;
			args = args->next;
		}
		ft_dprintf(cfg_shell()->debug, "\t\t-----------------\n");
	}
}

void		print_s_cmd(t_list *cmd_list)
{
	t_list			*args;
	int				n_arg;
	int				nb_args;
	t_simple_cmd	*cmd;

	n_arg = 0;
	nb_args = 0;
	cmd = (t_simple_cmd*)cmd_list->data;
	args = cmd->args;
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
	handle_assign(cmd);
	handle_redir(cmd);
	handle_args(args, n_arg, nb_args);
}

void		print_line(void)
{
	ft_dprintf(cfg_shell()->debug,
	"\t----------------------------------------\n");
}
