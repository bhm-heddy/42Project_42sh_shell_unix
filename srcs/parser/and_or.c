#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "sh.h"

int	p_add_and_or(t_token *token, t_parser *parser)
{
	t_cmd_table	*table;
	t_and_or	*and_or;
	t_list		*new;

	if (parser->state == S_PARSER_TABLE_START && !p_add_table(parser))
		return (0);
	table = (t_cmd_table *)parser->curr_table->data;
	and_or = (t_and_or *)table->curr_and_or->data;
	and_or->type = token->type;
	if (!(new = ft_lstnew(NULL, 0))
	|| (!(new->data = init_and_or())))
		return (0);
	table->curr_and_or->next = new;
	table->curr_and_or = new;
	parser->state = S_PARSER_ANDIF_PIPE;
	parser->pmt_prefix = token->type;
	return (1);
}
