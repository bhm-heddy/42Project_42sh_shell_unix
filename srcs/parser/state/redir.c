#include "parser.h"

void	p_init_redir_state(
		int (*table_builder[10][17])(t_token *, t_parser *))
{
	table_builder[S_PARSER_REDIR][TOKEN] = syn_err;
	table_builder[S_PARSER_REDIR][WORD] = p_file_name;
	table_builder[S_PARSER_REDIR][ASSIGNMENT_WORD] = syn_err;
	table_builder[S_PARSER_REDIR][NEWLINE] = syn_err;
	table_builder[S_PARSER_REDIR][IO_NUMBER] = syn_err;
	table_builder[S_PARSER_REDIR][AND_IF] = syn_err;
	table_builder[S_PARSER_REDIR][AMP] = syn_err;
	table_builder[S_PARSER_REDIR][OR_IF] = syn_err;
	table_builder[S_PARSER_REDIR][PIPE] = syn_err;
	table_builder[S_PARSER_REDIR][SEMI] = syn_err;
	table_builder[S_PARSER_REDIR][LESS] = syn_err;
	table_builder[S_PARSER_REDIR][DLESS] = syn_err;
	table_builder[S_PARSER_REDIR][GREAT] = syn_err;
	table_builder[S_PARSER_REDIR][DGREAT] = syn_err;
	table_builder[S_PARSER_REDIR][LESSAND] = syn_err;
	table_builder[S_PARSER_REDIR][GREATAND] = syn_err;
	table_builder[S_PARSER_REDIR][DLESSDASH] = syn_err;
}
