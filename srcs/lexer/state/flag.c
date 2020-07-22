#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

void	init_flag_state(int (*token_builder[9][12])(t_lexer *, char))
{
	token_builder[S_FLAG][C_INHIBITOR] = l_delim_flag;
	token_builder[S_FLAG][C_CONTROL] = l_flag_state_add;
	token_builder[S_FLAG][C_REDIR] = l_flag_state_add;
	token_builder[S_FLAG][C_NEWLINE] = l_flag_state_add;
	token_builder[S_FLAG][C_DIGIT] = l_flag_state_add;
	token_builder[S_FLAG][C_EXP] = l_flag_state_add;
	token_builder[S_FLAG][C_BLANK] = l_flag_state_add;
	token_builder[S_FLAG][C_EOI] = l_complete_str;
	token_builder[S_FLAG][C_BRACK] = l_delim_flag;
	token_builder[S_FLAG][C_EQU] = l_flag_state_add;
	token_builder[S_FLAG][C_HASH] = l_flag_state_add;
	token_builder[S_FLAG][C_OTHER] = l_flag_state_add;
}
