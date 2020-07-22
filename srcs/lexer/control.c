#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

int	l_build_control(t_lexer *lexer, char c)
{
	if (c == ';')
	{
		l_buffer_add(lexer, c);
		if (!l_create_token(lexer))
			return (0);
		lexer->curr_token->type = SEMI;
		l_buffer_flush(lexer);
		lexer->state = S_TK_START;
	}
	else
	{
		if (lexer->state == S_TK_START && !l_create_token(lexer))
			return (0);
		if ((ft_strequ(lexer->buffer, "&&") && c == '&')
		|| (ft_strequ(lexer->buffer, "||") && c == '|'))
			return (l_delim_control(lexer, c));
		if (ft_strchr("&|", c))
		{
			lexer->state = S_AMP_PIPE;
			l_buffer_add(lexer, c);
		}
	}
	return (1);
}

int	l_delim_control(t_lexer *lexer, char c)
{
	l_delim_token(lexer, c);
	lexer->state = S_TK_START;
	l_build_control(lexer, c);
	return (1);
}
