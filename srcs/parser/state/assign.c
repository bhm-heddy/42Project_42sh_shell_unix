#include "parser.h"

void	p_init_assign_state(
		int (*table_builder[10][17])(t_token *, t_parser *))
{
	table_builder[S_PARSER_ASSIGN][TOKEN] = syn_err;
	table_builder[S_PARSER_ASSIGN][WORD] = p_assign_val;
	table_builder[S_PARSER_ASSIGN][ASSIGNMENT_WORD] = syn_err;
	table_builder[S_PARSER_ASSIGN][NEWLINE] = p_set_start_state;
	table_builder[S_PARSER_ASSIGN][IO_NUMBER] = syn_err;
	table_builder[S_PARSER_ASSIGN][AND_IF] = p_add_and_or;
	table_builder[S_PARSER_ASSIGN][AMP] = p_add_amp;
	table_builder[S_PARSER_ASSIGN][OR_IF] = p_add_and_or;
	table_builder[S_PARSER_ASSIGN][PIPE] = p_add_cmd;
	table_builder[S_PARSER_ASSIGN][SEMI] = p_set_start_state;
	table_builder[S_PARSER_ASSIGN][LESS] = syn_err;
	table_builder[S_PARSER_ASSIGN][DLESS] = syn_err;
	table_builder[S_PARSER_ASSIGN][GREAT] = syn_err;
	table_builder[S_PARSER_ASSIGN][DGREAT] = syn_err;
	table_builder[S_PARSER_ASSIGN][LESSAND] = syn_err;
	table_builder[S_PARSER_ASSIGN][GREATAND] = syn_err;
	table_builder[S_PARSER_ASSIGN][DLESSDASH] = syn_err;
}
