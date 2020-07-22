#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

void	init_comment_state(int (*token_builder[9][12])(t_lexer *, char))
{
	token_builder[S_COMMENT][C_INHIBITOR] = l_do_nothing;
	token_builder[S_COMMENT][C_CONTROL] = l_do_nothing;
	token_builder[S_COMMENT][C_REDIR] = l_do_nothing;
	token_builder[S_COMMENT][C_NEWLINE] = l_end_comment;
	token_builder[S_COMMENT][C_DIGIT] = l_do_nothing;
	token_builder[S_COMMENT][C_EXP] = l_do_nothing;
	token_builder[S_COMMENT][C_BLANK] = l_do_nothing;
	token_builder[S_COMMENT][C_EOI] = l_end_comment;
	token_builder[S_COMMENT][C_BRACK] = l_do_nothing;
	token_builder[S_COMMENT][C_EQU] = l_do_nothing;
	token_builder[S_COMMENT][C_HASH] = l_do_nothing;
	token_builder[S_COMMENT][C_OTHER] = l_do_nothing;
}
