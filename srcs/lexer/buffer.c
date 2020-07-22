#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "sh.h"

void		l_buffer_flush(t_lexer *lexer)
{
	t_token		*token;

	token = lexer->curr_token;
	if (!token->str)
	{
		if (!(token->str = ft_strndup(lexer->buffer, lexer->buff_i)))
			ft_ex(EXMALLOC);
	}
	else if (!(token->str = ft_strnlclnjoin(token->str,
	lexer->buffer, lexer->buff_i)))
		ft_ex(EXMALLOC);
	ft_bzero(lexer->buffer, L_BUFF_SIZE);
	lexer->buff_i = 0;
}

int			l_buffer_add(t_lexer *lexer, char c)
{
	if (lexer->buff_i >= L_BUFF_SIZE)
		l_buffer_flush(lexer);
	lexer->buffer[lexer->buff_i] = c;
	lexer->buff_i++;
	return (1);
}
