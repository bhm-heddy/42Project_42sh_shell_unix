#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

int	l_is_quoting(t_lexer *lexer)
{
	if (!l_get_flag(lexer, F_DQUOTE)
	&& !l_get_flag(lexer, F_SQUOTE)
	&& !l_get_flag(lexer, F_BSLASH))
		return (0);
	return (1);
}

int	l_bslash_add(t_lexer *lexer, char c)
{
	if (c != '\n')
		l_buffer_add(lexer, c);
	l_unset_flag(lexer, F_BSLASH);
	return (1);
}

int	l_dquote_add(t_lexer *lexer, char c)
{
	if (c == '$')
		l_build_exp(lexer, c);
	else if (c == '\\')
		l_set_flag(lexer, F_BSLASH);
	else
		l_buffer_add(lexer, c);
	return (1);
}
