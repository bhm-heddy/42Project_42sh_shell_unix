#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "sh.h"
#include "exec.h"
#include "var.h"
#include "line_edition.h"

static char		*l_get_prompt_prefix(t_lexer *lexer)
{
	t_lexer_flag	flag;
	t_here_queue	*here;

	if ((flag = l_get_last_flag(lexer)))
	{
		if (flag == F_DQUOTE)
			return (ft_strdup("dquote> "));
		else if (flag == F_SQUOTE)
			return (ft_strdup("squote> "));
		else if (flag == F_BSLASH)
			return (ft_strdup("bslash> "));
		else if (flag == F_BRACKEXP)
			return (ft_strdup("braceparam> "));
	}
	else if ((here = l_get_last_here(lexer)))
		return (ft_strdup("heredoc> "));
	return (ft_strnew(0));
}

static int		l_get_prompt(t_lexer *lexer, char **new, char **pmt_prefix)
{
	if (cfg_shell()->interactive)
	{
		if (!(*pmt_prefix = l_get_prompt_prefix(lexer)))
			ft_ex(EXMALLOC);
	}
	else
		*pmt_prefix = NULL;
	if (!(*new = ft_prompt(*pmt_prefix, COLOR_SUBPROMPT)))
	{
		if (cfg_shell()->interactive)
			ft_strdel(pmt_prefix);
		return (0);
	}
	return (1);
}

static int		l_handle_flags(t_lexer *lexer, char **new, char **pmt_prefix)
{
	if (!**new && l_get_last_here(lexer))
	{
		if (cfg_shell()->interactive)
			ft_strdel(pmt_prefix);
		ft_strdel(new);
		return (l_hd_body_flush(lexer, 0));
	}
	else if (!**new && (l_get_last_flag(lexer) == F_SQUOTE
	|| l_get_last_flag(lexer) == F_DQUOTE))
	{
		if (cfg_shell()->interactive)
			ft_strdel(pmt_prefix);
		ft_strdel(new);
		return (0);
	}
	return (1);
}

int				l_complete_str(t_lexer *lexer, char c)
{
	size_t	pos;
	char	*new;
	char	*pmt_prefix;

	(void)c;
	new = NULL;
	pos = lexer->curr - *lexer->src;
	if (!l_get_prompt(lexer, &new, &pmt_prefix))
		return (0);
	if (!*new && (l_get_last_here(lexer)
	|| l_get_last_flag(lexer) == F_SQUOTE
	|| l_get_last_flag(lexer) == F_DQUOTE))
		return (l_handle_flags(lexer, &new, &pmt_prefix));
	if (!(*lexer->src = ft_strclnjoin(*lexer->src, new)))
		ft_ex(EXMALLOC);
	lexer->curr = *lexer->src + pos;
	if (cfg_shell()->interactive)
		ft_strdel(&pmt_prefix);
	return (1);
}
