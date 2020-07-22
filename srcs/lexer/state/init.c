#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "sh.h"

void	init_lexer_states(int (*token_builder[9][12])(t_lexer *, char))
{
	init_start_state(token_builder);
	init_heredoc_body_state(token_builder);
	init_amp_pipe_state(token_builder);
	init_redir_state(token_builder);
	init_exp_state(token_builder);
	init_word_state(token_builder);
	init_io_number_state(token_builder);
	init_flag_state(token_builder);
	init_comment_state(token_builder);
}
