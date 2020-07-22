#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

void	init_start_state(int (*token_builder[9][12])(t_lexer *, char))
{
	token_builder[S_TK_START][C_INHIBITOR] = l_build_inhib;
	token_builder[S_TK_START][C_CONTROL] = l_build_control;
	token_builder[S_TK_START][C_REDIR] = l_build_redir;
	token_builder[S_TK_START][C_NEWLINE] = l_build_newline;
	token_builder[S_TK_START][C_DIGIT] = l_build_digit;
	token_builder[S_TK_START][C_EXP] = l_build_exp;
	token_builder[S_TK_START][C_BLANK] = l_do_nothing;
	token_builder[S_TK_START][C_EOI] = l_do_nothing;
	token_builder[S_TK_START][C_BRACK] = l_build_word;
	token_builder[S_TK_START][C_EQU] = l_build_word;
	token_builder[S_TK_START][C_HASH] = l_comment_line;
	token_builder[S_TK_START][C_OTHER] = l_build_word;
}
