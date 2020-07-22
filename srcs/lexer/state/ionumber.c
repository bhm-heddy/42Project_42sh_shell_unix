#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

void	init_io_number_state(int (*token_builder[9][12])(t_lexer *, char))
{
	token_builder[S_IO_NUMBER][C_INHIBITOR] = l_build_inhib;
	token_builder[S_IO_NUMBER][C_CONTROL] = l_delim_control;
	token_builder[S_IO_NUMBER][C_REDIR] = l_delim_redir;
	token_builder[S_IO_NUMBER][C_NEWLINE] = l_delim_newline;
	token_builder[S_IO_NUMBER][C_DIGIT] = l_buffer_add;
	token_builder[S_IO_NUMBER][C_EXP] = l_build_exp;
	token_builder[S_IO_NUMBER][C_BLANK] = l_delim_token;
	token_builder[S_IO_NUMBER][C_EOI] = l_delim_token;
	token_builder[S_IO_NUMBER][C_BRACK] = l_build_word;
	token_builder[S_IO_NUMBER][C_EQU] = l_build_word;
	token_builder[S_IO_NUMBER][C_HASH] = l_build_word;
	token_builder[S_IO_NUMBER][C_OTHER] = l_build_word;
}
