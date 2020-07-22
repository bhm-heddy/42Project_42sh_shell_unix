#include "libft.h"
#include "lexer.h"
#include "parser.h"

int		p_create_redir(t_simple_cmd *cmd)
{
	t_list		*lst;
	t_redir		*redir;

	if (!(lst = ft_lstnew(NULL, 0))
	|| !(redir = init_redir()))
		return (0);
	lst->data = redir;
	if (!cmd->redir)
		cmd->redir = lst;
	else
		cmd->curr_redir->next = lst;
	cmd->curr_redir = lst;
	return (1);
}

int		p_add_io_num(t_token *token, t_parser *parser)
{
	t_cmd_table		*table;
	t_and_or		*and_or;
	t_simple_cmd	*cmd;
	t_redir			*redir;

	(void)token;
	if (parser->state == S_PARSER_TABLE_START && !p_add_table(parser))
		return (0);
	table = (t_cmd_table *)parser->curr_table->data;
	and_or = (t_and_or *)table->curr_and_or->data;
	cmd = (t_simple_cmd *)and_or->curr_s_cmd->data;
	if (!p_create_redir(cmd))
		return (0);
	redir = (t_redir *)cmd->curr_redir->data;
	if (!(redir->io_num = ft_strdup(token->str)))
		return (0);
	parser->prev_state = parser->state;
	parser->state = S_PARSER_IO_NUMBER;
	return (1);
}

int		p_add_redir(t_token *token, t_parser *parser)
{
	t_cmd_table		*table;
	t_and_or		*and_or;
	t_simple_cmd	*cmd;
	t_redir			*redir;

	if (parser->state == S_PARSER_TABLE_START && !p_add_table(parser))
		return (0);
	table = (t_cmd_table *)parser->curr_table->data;
	and_or = (t_and_or *)table->curr_and_or->data;
	cmd = (t_simple_cmd *)and_or->curr_s_cmd->data;
	if (parser->state != S_PARSER_IO_NUMBER && !p_create_redir(cmd))
		return (0);
	redir = (t_redir *)cmd->curr_redir->data;
	redir->type = token->type;
	if (parser->state != S_PARSER_IO_NUMBER)
		parser->prev_state = parser->state;
	if (token->type == DLESS || token->type == DLESSDASH)
		parser->state = S_PARSER_DELIM;
	else
		parser->state = S_PARSER_REDIR;
	return (1);
}

int		p_add_redir_delim(t_token *token, t_parser *parser)
{
	t_cmd_table		*table;
	t_and_or		*and_or;
	t_simple_cmd	*cmd;
	t_redir			*redir;

	table = (t_cmd_table *)parser->curr_table->data;
	and_or = (t_and_or *)table->curr_and_or->data;
	cmd = (t_simple_cmd *)and_or->curr_s_cmd->data;
	redir = (t_redir *)cmd->curr_redir->data;
	if (!(redir->delim = ft_strdup(token->str)))
		return (0);
	parser->state = S_PARSER_REDIR;
	return (1);
}
