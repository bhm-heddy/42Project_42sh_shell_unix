#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "sh.h"

void		init_token(t_token *token)
{
	token->str = NULL;
	token->type = 0;
	token->len = 0;
}

int			l_create_token(t_lexer *lexer)
{
	if (!(lexer->curr_token = (t_token *)ft_memalloc(sizeof(t_token))))
		ft_ex(EXMALLOC);
	init_token(lexer->curr_token);
	if (!ft_lstpush(&lexer->token_lst, lexer->curr_token, sizeof(t_token)))
		ft_ex(EXMALLOC);
	return (1);
}

int			l_delim_token(t_lexer *lexer, char c)
{
	if (l_get_flag(lexer, F_HD_DELIM))
	{
		l_unset_flag(lexer, F_HD_DELIM);
		l_flush_delim(lexer);
		if (!l_create_token(lexer))
			return (0);
		lexer->curr_here->token = lexer->curr_token;
		lexer->curr_token->type = WORD;
		lexer->state = S_TK_START;
		return (1);
	}
	l_buffer_flush(lexer);
	if (lexer->curr_token->type == IO_NUMBER && (!ft_strchr("<>", c) || !c))
		lexer->curr_token->type = WORD;
	else if (lexer->curr_token->type == TOKEN)
		l_set_token_type(lexer, c);
	if (lexer->curr_token->type == DLESS
	|| lexer->curr_token->type == DLESSDASH)
	{
		l_set_flag(lexer, F_HD_DELIM);
		l_create_here_queue(lexer);
		l_set_flag(lexer, F_HEREDOC);
	}
	lexer->state = S_TK_START;
	return (1);
}
