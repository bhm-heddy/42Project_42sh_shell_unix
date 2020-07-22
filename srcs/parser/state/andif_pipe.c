#include "parser.h"

void	p_init_andif_pipe_state(
		int (*table_builder[10][17])(t_token *, t_parser *))
{
	table_builder[S_PARSER_ANDIF_PIPE][TOKEN] = syn_err;
	table_builder[S_PARSER_ANDIF_PIPE][WORD] = p_cmd_name;
	table_builder[S_PARSER_ANDIF_PIPE][ASSIGNMENT_WORD] = p_add_assign;
	table_builder[S_PARSER_ANDIF_PIPE][NEWLINE] = p_skip;
	table_builder[S_PARSER_ANDIF_PIPE][IO_NUMBER] = p_add_io_num;
	table_builder[S_PARSER_ANDIF_PIPE][AND_IF] = syn_err;
	table_builder[S_PARSER_ANDIF_PIPE][AMP] = syn_err;
	table_builder[S_PARSER_ANDIF_PIPE][OR_IF] = syn_err;
	table_builder[S_PARSER_ANDIF_PIPE][PIPE] = syn_err;
	table_builder[S_PARSER_ANDIF_PIPE][SEMI] = syn_err;
	table_builder[S_PARSER_ANDIF_PIPE][LESS] = p_add_redir;
	table_builder[S_PARSER_ANDIF_PIPE][DLESS] = p_add_redir;
	table_builder[S_PARSER_ANDIF_PIPE][GREAT] = p_add_redir;
	table_builder[S_PARSER_ANDIF_PIPE][DGREAT] = p_add_redir;
	table_builder[S_PARSER_ANDIF_PIPE][LESSAND] = p_add_redir;
	table_builder[S_PARSER_ANDIF_PIPE][GREATAND] = p_add_redir;
	table_builder[S_PARSER_ANDIF_PIPE][DLESSDASH] = p_add_redir;
}
