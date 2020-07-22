#include "parser.h"

void	p_init_arg_assign_state(
		int (*table_builder[10][17])(t_token *, t_parser *))
{
	table_builder[S_PARSER_ARG_ASSIGN][TOKEN] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][WORD] = p_assign_join;
	table_builder[S_PARSER_ARG_ASSIGN][ASSIGNMENT_WORD] = p_assign_join;
	table_builder[S_PARSER_ARG_ASSIGN][NEWLINE] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][IO_NUMBER] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][AND_IF] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][AMP] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][OR_IF] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][PIPE] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][SEMI] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][LESS] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][DLESS] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][GREAT] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][DGREAT] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][LESSAND] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][GREATAND] = syn_err;
	table_builder[S_PARSER_ARG_ASSIGN][DLESSDASH] = syn_err;
}
