#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

int			l_comment_line(t_lexer *lexer, char c)
{
	(void)c;
	lexer->state = S_COMMENT;
	return (1);
}

int			l_end_comment(t_lexer *lexer, char c)
{
	(void)c;
	lexer->state = S_TK_START;
	return (1);
}
