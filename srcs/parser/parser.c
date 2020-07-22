#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "var.h"
#include "line_edition.h"
#include "sh.h"

void	init_parser(t_parser *parser)
{
	parser->state = S_PARSER_TABLE_START;
	parser->prev_state = S_PARSER_TABLE_START;
	parser->space_flag = 0;
	parser->table = NULL;
	parser->curr_table = NULL;
}

int		p_process_token(t_token *token, t_parser *parser,
	int (*table_builder[10][17])(t_token *, t_parser *))
{
	if (!table_builder[parser->state][token->type](token, parser))
		return (0);
	return (1);
}

int		p_tokeniter(t_list *token, t_parser *parser,
		int (*table_builder[10][17])(t_token *, t_parser *))
{
	while (token)
	{
		if (!p_process_token(token->data, parser, table_builder))
			return (0);
		token = token->next;
	}
	return (1);
}

int		ft_parser(t_lexer *lexer, t_parser *parser)
{
	int		(*table_builder[10][17])(t_token *, t_parser *);
	char	*pmt;
	char	*pmt_prefix;

	if (!lexer || !parser)
		return (0);
	p_init_state_machine(table_builder);
	reset_alias_list();
	p_tokeniter(lexer->token_lst, parser, table_builder);
	while (parser->state == S_PARSER_ANDIF_PIPE)
	{
		ft_lstdel(&lexer->token_lst, del_token);
		if (!(pmt_prefix = p_get_prompt_prefix(parser))
		|| !(pmt = ft_prompt(pmt_prefix, COLOR_SUBPROMPT)))
		{
			ft_strdel(&pmt_prefix);
			return (0);
		}
		ft_lexer(&pmt, lexer);
		ft_strdel(&pmt);
		ft_strdel(&pmt_prefix);
		p_tokeniter(lexer->token_lst, parser, table_builder);
	}
	ft_lstdel(&cfg_shell()->alias_cpy, del_struct_tvar);
	return (1);
}
