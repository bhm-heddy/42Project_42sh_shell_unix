#include "libft.h"
#include "lexer.h"
#include "parser.h"

t_assignment	*init_assignment(void)
{
	t_assignment	*assign;

	assign = (t_assignment *)ft_memalloc(sizeof(t_assignment));
	return (assign);
}

t_redir			*init_redir(void)
{
	t_redir		*redir;

	redir = (t_redir *)ft_memalloc(sizeof(t_redir));
	redir->io_num = NULL;
	return (redir);
}

t_simple_cmd	*init_simple_cmd(void)
{
	t_simple_cmd	*cmd;

	cmd = (t_simple_cmd *)ft_memalloc(sizeof(t_simple_cmd));
	return (cmd);
}

t_and_or		*init_and_or(void)
{
	t_and_or	*and_or;

	if (!(and_or = (t_and_or *)ft_memalloc(sizeof(t_and_or)))
	|| !(and_or->s_cmd = ft_lstnew(NULL, 0))
	|| !(and_or->s_cmd->data = init_simple_cmd()))
		return (NULL);
	and_or->curr_s_cmd = and_or->s_cmd;
	return (and_or);
}

t_cmd_table		*init_cmd_table(void)
{
	t_cmd_table	*table;

	if (!(table = (t_cmd_table *)ft_memalloc(sizeof(t_cmd_table)))
	|| !(table->and_or = ft_lstnew(NULL, 0))
	|| !(table->and_or->data = init_and_or()))
		return (NULL);
	table->curr_and_or = table->and_or;
	return (table);
}
