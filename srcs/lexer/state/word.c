#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

void	init_word_state(int (*token_builder[9][12])(t_lexer *, char))
{
	token_builder[S_TK_WORD][C_INHIBITOR] = l_build_inhib;
	token_builder[S_TK_WORD][C_CONTROL] = l_delim_control;
	token_builder[S_TK_WORD][C_REDIR] = l_delim_redir;
	token_builder[S_TK_WORD][C_NEWLINE] = l_delim_newline;
	token_builder[S_TK_WORD][C_DIGIT] = l_buffer_add;
	token_builder[S_TK_WORD][C_EXP] = l_build_exp;
	token_builder[S_TK_WORD][C_BLANK] = l_delim_token;
	token_builder[S_TK_WORD][C_EOI] = l_delim_token;
	token_builder[S_TK_WORD][C_BRACK] = l_buffer_add;
	token_builder[S_TK_WORD][C_EQU] = l_delim_equ;
	token_builder[S_TK_WORD][C_HASH] = l_buffer_add;
	token_builder[S_TK_WORD][C_OTHER] = l_buffer_add;
}
