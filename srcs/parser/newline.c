#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "sh.h"

int	p_add_table(t_parser *parser)
{
	t_cmd_table	*table;

	if (!(table = init_cmd_table()))
		return (0);
	if (!ft_lstpush(&parser->table, table, sizeof(t_cmd_table)))
		return (0);
	parser->curr_table = ft_lstgettail(parser->table);
	return (1);
}
