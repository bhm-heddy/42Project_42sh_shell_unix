#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

void	init_exp_state(int (*token_builder[9][12])(t_lexer *, char))
{
	token_builder[S_EXP][C_INHIBITOR] = l_build_inhib;
	token_builder[S_EXP][C_CONTROL] = l_delim_control;
	token_builder[S_EXP][C_REDIR] = l_delim_redir;
	token_builder[S_EXP][C_NEWLINE] = l_delim_newline;
	token_builder[S_EXP][C_DIGIT] = l_buffer_add;
	token_builder[S_EXP][C_EXP] = l_build_exp;
	token_builder[S_EXP][C_BLANK] = l_delim_token;
	token_builder[S_EXP][C_EOI] = l_delim_token;
	token_builder[S_EXP][C_BRACK] = l_exp_brack;
	token_builder[S_EXP][C_EQU] = l_buffer_add;
	token_builder[S_EXP][C_HASH] = l_exp_add;
	token_builder[S_EXP][C_OTHER] = l_exp_add;
}
