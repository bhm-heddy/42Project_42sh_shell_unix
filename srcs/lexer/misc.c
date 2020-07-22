#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "sh.h"
#include "exec.h"
#include "var.h"
#include "line_edition.h"

int			lex_err(t_lexer *lexer, char c)
{
	(void)lexer;
	(void)c;
	ft_dprintf(2, "lexing error\n");
	exit(1);
	return (1);
}

char		l_get_char(t_lexer *lexer)
{
	if (!*(lexer->curr))
		return (0);
	return (*lexer->curr++);
}

t_char_type	l_get_char_type(char c)
{
	if (c == 0)
		return (C_EOI);
	else if (c == '=')
		return (C_EQU);
	else if (c == '\n')
		return (C_NEWLINE);
	else if (c == '$')
		return (C_EXP);
	else if (c == '#')
		return (C_HASH);
	else if (ft_strchr("\"\'\\", c))
		return (C_INHIBITOR);
	else if (ft_strchr("&|;", c))
		return (C_CONTROL);
	else if (ft_strchr("<>", c))
		return (C_REDIR);
	else if (ft_isdigit(c))
		return (C_DIGIT);
	else if (ft_strchr(" \t", c))
		return (C_BLANK);
	else if (ft_strchr("{}", c))
		return (C_BRACK);
	else
		return (C_OTHER);
}
