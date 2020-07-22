#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "sh.h"

static void		print_lexer_debug(t_lexer *lexer, char c, t_lexer_flag flag)
{
	char	*state;
	char	*flag_str;

	state = NULL;
	flag_str = NULL;
	if (c == '\n')
		ft_dprintf(cfg_shell()->debug, "->\t%s\t%20s\t%s\n\n",
		"\\n", (state = get_state_str(lexer)),
		(flag_str = get_flag_name(flag)));
	else
		ft_dprintf(cfg_shell()->debug, "->\t%c\t%20s\t%s\n",
		c, (state = get_state_str(lexer)),
		(flag_str = get_flag_name(flag)));
	ft_strdel(&state);
	ft_strdel(&flag_str);
}

int				do_lexing(t_lexer *lexer,
				int (*token_builder[9][12])(t_lexer *, char))
{
	char			c;
	t_lexer_flag	flag;

	while ((c = l_get_char(lexer)))
	{
		flag = l_get_last_flag(lexer);
		if (!token_builder[lexer->state][l_get_char_type(c)](lexer, c))
			return (0);
		if (cfg_shell()->debug)
			print_lexer_debug(lexer, c, flag);
	}
	if (!token_builder[lexer->state][l_get_char_type(c)](lexer, c))
		return (0);
	return (1);
}

static int		lexer_error_display(t_lexer *lexer)
{
	if (l_get_last_flag(lexer) || l_get_last_here(lexer))
		ft_dprintf(2, "%s: syntax error: unexpected end of file\n",
		PROJECT);
	return (0);
}

int				ft_lexer(char **str, t_lexer *lexer)
{
	int	(*token_builder[9][12])(t_lexer *, char);

	lexer->src = str;
	lexer->curr = *str;
	init_lexer_states(token_builder);
	if (!do_lexing(lexer, token_builder))
		return (lexer_error_display(lexer));
	while (l_get_last_flag(lexer) || l_get_last_here(lexer))
		if (!do_lexing(lexer, token_builder))
			return (lexer_error_display(lexer));
	return (1);
}
