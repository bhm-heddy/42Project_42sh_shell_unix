#include "parser.h"

void	p_init_cmd_wait_state(
		int (*table_builder[10][17])(t_token *, t_parser *))
{
	table_builder[S_PARSER_CMD_START][TOKEN] = syn_err;
	table_builder[S_PARSER_CMD_START][WORD] = p_cmd_name;
	table_builder[S_PARSER_CMD_START][ASSIGNMENT_WORD] = p_add_assign;
	table_builder[S_PARSER_CMD_START][NEWLINE] = p_skip;
	table_builder[S_PARSER_CMD_START][IO_NUMBER] = p_add_io_num;
	table_builder[S_PARSER_CMD_START][AND_IF] = p_add_and_or;
	table_builder[S_PARSER_CMD_START][AMP] = p_add_amp;
	table_builder[S_PARSER_CMD_START][OR_IF] = syn_err;
	table_builder[S_PARSER_CMD_START][PIPE] = p_add_cmd;
	table_builder[S_PARSER_CMD_START][SEMI] = p_set_start_state;
	table_builder[S_PARSER_CMD_START][LESS] = p_add_redir;
	table_builder[S_PARSER_CMD_START][DLESS] = p_add_redir;
	table_builder[S_PARSER_CMD_START][GREAT] = p_add_redir;
	table_builder[S_PARSER_CMD_START][DGREAT] = p_add_redir;
	table_builder[S_PARSER_CMD_START][LESSAND] = p_add_redir;
	table_builder[S_PARSER_CMD_START][GREATAND] = p_add_redir;
	table_builder[S_PARSER_CMD_START][DLESSDASH] = p_add_redir;
}
