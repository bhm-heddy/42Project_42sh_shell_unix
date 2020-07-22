#include "libft.h"
#include "parser.h"
#include "lexer.h"

void	del_assign(void *data, size_t size)
{
	t_assignment	*assign;

	(void)size;
	assign = (t_assignment *)data;
	ft_strdel(&assign->var);
	ft_strdel(&assign->val);
	free(data);
}

void	del_redir(void *data, size_t size)
{
	t_redir	*redir;

	(void)size;
	redir = (t_redir *)data;
	ft_strdel(&redir->delim);
	ft_strdel(&redir->io_num);
	ft_strdel(&redir->file);
	free(data);
}

void	del_simple_cmd(void *data, size_t size)
{
	t_simple_cmd	*cmd;

	(void)size;
	cmd = (t_simple_cmd *)data;
	ft_lstdel(&cmd->redir, del_redir);
	ft_lstdel(&cmd->assign, del_assign);
	ft_lstdel(&cmd->args, del_str);
	ft_strdel(&cmd->cmd_name);
	free(cmd->av);
	free(data);
}

void	del_and_or(void *data, size_t size)
{
	t_and_or	*and_or;

	(void)size;
	and_or = (t_and_or *)data;
	ft_lstdel(&and_or->s_cmd, del_simple_cmd);
	ft_strdel(&and_or->str);
	free(data);
}

void	del_cmd_table(void *data, size_t size)
{
	t_cmd_table	*table;

	(void)size;
	table = (t_cmd_table *)data;
	ft_lstdel(&table->and_or, del_and_or);
	free(data);
}
