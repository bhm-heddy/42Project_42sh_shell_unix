#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

int	l_delim_exp(t_lexer *lexer, char c)
{
	l_delim_token(lexer, c);
	l_build_exp(lexer, c);
	return (1);
}

int	l_build_exp(t_lexer *lexer, char c)
{
	if (lexer->state == S_TK_START && !l_get_flag(lexer, F_HD_DELIM)
	&& !l_create_token(lexer))
		return (0);
	l_buffer_add(lexer, c);
	lexer->state = S_EXP;
	if (!l_get_flag(lexer, F_HD_DELIM))
		lexer->curr_token->type = WORD;
	return (1);
}

int	l_exp_brack(t_lexer *lexer, char c)
{
	l_buffer_add(lexer, c);
	if (c == '{')
	{
		l_add_flag(lexer, c);
		lexer->state = S_FLAG;
	}
	else
	{
		ft_lstdeltail(&lexer->flag_queue, del_flag_queue);
		if (l_get_last_flag(lexer) > 0)
			lexer->state = S_FLAG;
		else
			lexer->state = S_TK_WORD;
	}
	return (1);
}

int	l_exp_add(t_lexer *lexer, char c)
{
	l_buffer_add(lexer, c);
	if (l_get_last_flag(lexer))
		lexer->state = S_FLAG;
	return (1);
}
