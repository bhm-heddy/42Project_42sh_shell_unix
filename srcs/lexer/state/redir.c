#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

void	init_redir_state(int (*token_builder[9][12])(t_lexer *, char))
{
	token_builder[S_TK_REDIR][C_INHIBITOR] = l_delim_inhib;
	token_builder[S_TK_REDIR][C_CONTROL] = l_build_redir;
	token_builder[S_TK_REDIR][C_REDIR] = l_build_redir;
	token_builder[S_TK_REDIR][C_NEWLINE] = l_delim_newline;
	token_builder[S_TK_REDIR][C_DIGIT] = l_delim_digit;
	token_builder[S_TK_REDIR][C_EXP] = l_delim_exp;
	token_builder[S_TK_REDIR][C_BLANK] = l_delim_token;
	token_builder[S_TK_REDIR][C_EOI] = l_do_nothing;
	token_builder[S_TK_REDIR][C_BRACK] = l_delim_word;
	token_builder[S_TK_REDIR][C_EQU] = l_delim_word;
	token_builder[S_TK_REDIR][C_HASH] = l_delim_word;
	token_builder[S_TK_REDIR][C_OTHER] = l_delim_word;
}
