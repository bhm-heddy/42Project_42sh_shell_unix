#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

void	init_amp_pipe_state(int (*token_builder[9][12])(t_lexer *, char))
{
	token_builder[S_AMP_PIPE][C_INHIBITOR] = l_delim_inhib;
	token_builder[S_AMP_PIPE][C_CONTROL] = l_build_control;
	token_builder[S_AMP_PIPE][C_REDIR] = l_delim_redir;
	token_builder[S_AMP_PIPE][C_NEWLINE] = l_delim_newline;
	token_builder[S_AMP_PIPE][C_DIGIT] = l_delim_digit;
	token_builder[S_AMP_PIPE][C_EXP] = l_delim_exp;
	token_builder[S_AMP_PIPE][C_BLANK] = l_delim_token;
	token_builder[S_AMP_PIPE][C_EOI] = l_delim_token;
	token_builder[S_AMP_PIPE][C_BRACK] = l_delim_word;
	token_builder[S_AMP_PIPE][C_EQU] = l_delim_word;
	token_builder[S_AMP_PIPE][C_HASH] = l_delim_word;
	token_builder[S_AMP_PIPE][C_OTHER] = l_delim_word;
}
