#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

int	l_delim_digit(t_lexer *lexer, char c)
{
	l_delim_token(lexer, c);
	l_build_digit(lexer, c);
	return (1);
}

int	l_build_digit(t_lexer *lexer, char c)
{
	l_buffer_add(lexer, c);
	if (lexer->state == S_TK_START && !l_create_token(lexer))
		return (0);
	lexer->state = S_IO_NUMBER;
	lexer->curr_token->type = IO_NUMBER;
	return (1);
}
