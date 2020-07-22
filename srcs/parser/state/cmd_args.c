#include "parser.h"

void	p_init_args_wait_state(
		int (*table_builder[10][17])(t_token *, t_parser *))
{
	table_builder[S_PARSER_CMD_ARGS][TOKEN] = syn_err;
	table_builder[S_PARSER_CMD_ARGS][WORD] = p_add_arg;
	table_builder[S_PARSER_CMD_ARGS][ASSIGNMENT_WORD] = p_add_assign_arg;
	table_builder[S_PARSER_CMD_ARGS][NEWLINE] = p_set_start_state;
	table_builder[S_PARSER_CMD_ARGS][IO_NUMBER] = p_add_io_num;
	table_builder[S_PARSER_CMD_ARGS][AND_IF] = p_add_and_or;
	table_builder[S_PARSER_CMD_ARGS][AMP] = p_add_amp;
	table_builder[S_PARSER_CMD_ARGS][OR_IF] = p_add_and_or;
	table_builder[S_PARSER_CMD_ARGS][PIPE] = p_add_cmd;
	table_builder[S_PARSER_CMD_ARGS][SEMI] = p_set_start_state;
	table_builder[S_PARSER_CMD_ARGS][LESS] = p_add_redir;
	table_builder[S_PARSER_CMD_ARGS][DLESS] = p_add_redir;
	table_builder[S_PARSER_CMD_ARGS][GREAT] = p_add_redir;
	table_builder[S_PARSER_CMD_ARGS][DGREAT] = p_add_redir;
	table_builder[S_PARSER_CMD_ARGS][LESSAND] = p_add_redir;
	table_builder[S_PARSER_CMD_ARGS][GREATAND] = p_add_redir;
	table_builder[S_PARSER_CMD_ARGS][DLESSDASH] = p_add_redir;
}
