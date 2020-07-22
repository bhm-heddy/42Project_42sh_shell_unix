#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"

int	l_set_ctrl_type(t_lexer *lexer, char c)
{
	(void)c;
	if (ft_strnequ(lexer->curr_token->str, "&&", 2))
		lexer->curr_token->type = AND_IF;
	else if (ft_strnequ(lexer->curr_token->str, "&", 1))
		lexer->curr_token->type = AMP;
	else if (ft_strnequ(lexer->curr_token->str, "||", 2))
		lexer->curr_token->type = OR_IF;
	else if (ft_strnequ(lexer->curr_token->str, "|", 1))
		lexer->curr_token->type = PIPE;
	return (1);
}

int	l_set_redir_type(t_lexer *lexer, char c)
{
	(void)c;
	if (ft_strnequ(lexer->curr_token->str, "<<-", 3))
		lexer->curr_token->type = DLESSDASH;
	else if (ft_strnequ(lexer->curr_token->str, "<<", 2))
		lexer->curr_token->type = DLESS;
	else if (ft_strnequ(lexer->curr_token->str, ">>", 2))
		lexer->curr_token->type = DGREAT;
	else if (ft_strnequ(lexer->curr_token->str, "<&", 2))
		lexer->curr_token->type = LESSAND;
	else if (ft_strnequ(lexer->curr_token->str, ">&", 2))
		lexer->curr_token->type = GREATAND;
	else if (ft_strnequ(lexer->curr_token->str, "<", 1))
		lexer->curr_token->type = LESS;
	else if (ft_strnequ(lexer->curr_token->str, ">", 1))
		lexer->curr_token->type = GREAT;
	return (1);
}

int	l_set_word_type(t_lexer *lexer, char c)
{
	int	i;

	i = -1;
	while (lexer->curr_token->str[++i])
		if (!ft_isdigit(lexer->curr_token->str[i]))
		{
			lexer->curr_token->type = WORD;
			return (1);
		}
	if (ft_strchr("<>", c))
		lexer->curr_token->type = IO_NUMBER;
	else
		lexer->curr_token->type = WORD;
	return (1);
}

int	l_set_token_type(t_lexer *lexer, char c)
{
	if (lexer->state == S_TK_START)
		return (0);
	else if (lexer->state == S_HD_BODY)
		l_set_word_type(lexer, c);
	else if (lexer->state == S_AMP_PIPE)
		l_set_ctrl_type(lexer, c);
	else if (lexer->state == S_TK_REDIR)
		l_set_redir_type(lexer, c);
	else if (lexer->state == S_TK_WORD)
		l_set_word_type(lexer, c);
	else if (lexer->state == S_IO_NUMBER)
		l_set_word_type(lexer, c);
	else
		lex_err(lexer, c);
	return (1);
}
