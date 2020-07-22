#include "parser.h"

void	p_init_delim_state(int (*table_builder[10][17])(t_token *, t_parser *))
{
	table_builder[S_PARSER_DELIM][TOKEN] = syn_err;
	table_builder[S_PARSER_DELIM][WORD] = p_add_redir_delim;
	table_builder[S_PARSER_DELIM][ASSIGNMENT_WORD] = syn_err;
	table_builder[S_PARSER_DELIM][NEWLINE] = syn_err;
	table_builder[S_PARSER_DELIM][IO_NUMBER] = syn_err;
	table_builder[S_PARSER_DELIM][AND_IF] = syn_err;
	table_builder[S_PARSER_DELIM][AMP] = syn_err;
	table_builder[S_PARSER_DELIM][OR_IF] = syn_err;
	table_builder[S_PARSER_DELIM][PIPE] = syn_err;
	table_builder[S_PARSER_DELIM][SEMI] = syn_err;
	table_builder[S_PARSER_DELIM][LESS] = syn_err;
	table_builder[S_PARSER_DELIM][DLESS] = syn_err;
	table_builder[S_PARSER_DELIM][GREAT] = syn_err;
	table_builder[S_PARSER_DELIM][DGREAT] = syn_err;
	table_builder[S_PARSER_DELIM][LESSAND] = syn_err;
	table_builder[S_PARSER_DELIM][GREATAND] = syn_err;
	table_builder[S_PARSER_DELIM][DLESSDASH] = syn_err;
}
