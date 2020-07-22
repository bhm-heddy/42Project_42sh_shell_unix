#include "parser.h"

void	p_init_start_state(int (*table_builder[10][17])(t_token *, t_parser *))
{
	table_builder[S_PARSER_TABLE_START][TOKEN] = syn_err;
	table_builder[S_PARSER_TABLE_START][WORD] = p_cmd_name;
	table_builder[S_PARSER_TABLE_START][ASSIGNMENT_WORD] = p_add_assign;
	table_builder[S_PARSER_TABLE_START][NEWLINE] = p_skip;
	table_builder[S_PARSER_TABLE_START][IO_NUMBER] = p_add_io_num;
	table_builder[S_PARSER_TABLE_START][AND_IF] = syn_err;
	table_builder[S_PARSER_TABLE_START][AMP] = syn_err;
	table_builder[S_PARSER_TABLE_START][OR_IF] = syn_err;
	table_builder[S_PARSER_TABLE_START][PIPE] = syn_err;
	table_builder[S_PARSER_TABLE_START][SEMI] = syn_err;
	table_builder[S_PARSER_TABLE_START][LESS] = p_add_redir;
	table_builder[S_PARSER_TABLE_START][DLESS] = p_add_redir;
	table_builder[S_PARSER_TABLE_START][GREAT] = p_add_redir;
	table_builder[S_PARSER_TABLE_START][DGREAT] = p_add_redir;
	table_builder[S_PARSER_TABLE_START][LESSAND] = p_add_redir;
	table_builder[S_PARSER_TABLE_START][GREATAND] = p_add_redir;
	table_builder[S_PARSER_TABLE_START][DLESSDASH] = p_add_redir;
}
