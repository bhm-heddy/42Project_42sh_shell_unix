#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "sh.h"
#include "debug.h"

void	print_assignment(t_list *assignment)
{
	t_assignment	*assign;

	assign = (t_assignment *)assignment->data;
	ft_dprintf(cfg_shell()->debug, "\t\t| %13s | %13s |\n",
	assign->var, assign->val);
}

void	print_redir(t_list *redirection)
{
	t_redir		*redir;
	char		*operator;

	redir = (t_redir *)redirection->data;
	operator = get_redir_op(redir->type);
	if (redir->io_num >= 0)
		ft_dprintf(cfg_shell()->debug, "\t\t| %7s | %6s | %10s |\n",
		redir->io_num, operator, redir->file);
	else
		ft_dprintf(cfg_shell()->debug, "\t\t| %7c | %6s | %10s |\n",
		'-', operator, redir->file);
	free(operator);
}

void	print_andor(t_list *and_or)
{
	t_and_or	*and_or_cont;
	t_list		*cmd_list;
	int			n_cmd;
	char		*str;

	n_cmd = 1;
	and_or_cont = (t_and_or *)and_or->data;
	cmd_list = (t_list*)and_or_cont->s_cmd;
	print_line();
	ft_dprintf(cfg_shell()->debug, "\t| %10s | %10s | %10s |\n", "type",
	"cmd_nb", "background");
	ft_dprintf(cfg_shell()->debug, "\t| %10s | %10d | %10d |\n",
	(str = get_and_or_type_str(and_or_cont)), get_nb_cmd(cmd_list),
	and_or_cont->background);
	ft_strdel(&str);
	print_line();
	while (cmd_list)
	{
		ft_dprintf(cfg_shell()->debug, "\t\tcmd %d:\n", n_cmd);
		print_s_cmd(cmd_list);
		n_cmd++;
		cmd_list = cmd_list->next;
	}
	ft_dprintf(cfg_shell()->debug, "\n");
}

void	print_cmd_table(t_list *table)
{
	t_list		*and_or;
	t_cmd_table	*table_cont;
	int			n_andor;

	n_andor = 1;
	table_cont = (t_cmd_table *)table->data;
	if (table_cont)
	{
		ft_dprintf(cfg_shell()->debug, "table=%p\n", table_cont);
		ft_dprintf(cfg_shell()->debug, "--------------\n");
		ft_dprintf(cfg_shell()->debug, "| %10s |\n", "and_or nb");
		ft_dprintf(cfg_shell()->debug, "| %10d |\n",
		get_nb_and_or(table_cont->and_or));
		ft_dprintf(cfg_shell()->debug, "--------------\n\n");
	}
	and_or = table_cont->and_or;
	while (and_or)
	{
		ft_dprintf(cfg_shell()->debug, "\tand_or %d:\n", n_andor);
		print_andor(and_or);
		n_andor++;
		and_or = and_or->next;
	}
}

void	print_parser(t_parser *parser)
{
	t_list	*table;
	int		i;

	i = 1;
	table = parser->table;
	while (table)
	{
		ft_dprintf(cfg_shell()->debug, "table %d\n", i++);
		print_cmd_table(table);
		table = table->next;
	}
}
