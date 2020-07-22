#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "sh.h"
#include "analyzer.h"

t_here_queue	*l_get_last_here(t_lexer *lexer)
{
	t_list		*here;

	here = ft_lstgettail(lexer->here_queue);
	if (here && here->data)
		return ((t_here_queue *)here->data);
	return (NULL);
}

int				l_create_flag_queue(t_lexer *lexer)
{
	if (!(lexer->curr_flag = (t_lexer_flag *)ft_memalloc(sizeof(t_lexer_flag))))
		ft_ex(EXMALLOC);
	if (!ft_lstpush(&lexer->flag_queue, lexer->curr_flag, sizeof(t_lexer_flag)))
		ft_ex(EXMALLOC);
	return (1);
}

int				l_create_here_queue(t_lexer *lexer)
{
	if (!(lexer->curr_here = (t_here_queue *)ft_memalloc(sizeof(t_here_queue))))
		ft_ex(EXMALLOC);
	if (!ft_lstpush(&lexer->here_queue, lexer->curr_here, sizeof(t_here_queue)))
		ft_ex(EXMALLOC);
	return (1);
}

void			l_flush_delim(t_lexer *lexer)
{
	if (!(lexer->curr_here->delim = ft_strndup(lexer->buffer, lexer->buff_i))
	|| !l_create_token(lexer)
	|| !(lexer->curr_token->str = ft_strndup(lexer->buffer, lexer->buff_i)))
		ft_ex(EXMALLOC);
	lexer->curr_token->type = WORD;
	ft_bzero(lexer->buffer, L_BUFF_SIZE);
	lexer->buff_i = 0;
	if (!(lexer->curr_here->delim = a_quote_removal(
	&lexer->curr_here->delim)))
		ft_ex(EXMALLOC);
	if (!(lexer->curr_token->str = a_quote_removal(
	&lexer->curr_token->str)))
		ft_ex(EXMALLOC);
}

int				l_hd_body_flush(t_lexer *lexer, char c)
{
	if (ft_strequ(lexer->buffer, lexer->curr_here->delim) || !c)
	{
		ft_bzero(lexer->buffer, L_BUFF_SIZE);
		lexer->buff_i = 0;
		ft_lstdelhead(&lexer->here_queue, &del_here_queue);
		if (lexer->here_queue)
		{
			lexer->curr_here = lexer->here_queue->data;
			lexer->curr_token = lexer->curr_here->token;
		}
		else
			lexer->curr_here = NULL;
		if (!lexer->curr_here)
		{
			lexer->state = S_TK_START;
			l_unset_flag(lexer, F_HEREDOC);
		}
	}
	else
	{
		l_buffer_add(lexer, c);
		l_buffer_flush(lexer);
	}
	return (1);
}
