#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "sh.h"
#include "debug.h"

static char	**token_debug_init(void)
{
	char	**tab;

	tab = NULL;
	if (!(tab = (char **)malloc(sizeof(char *) * 18)))
		ft_ex(EXMALLOC);
	tab[TOKEN] = ft_strdup("TOKEN");
	tab[WORD] = ft_strdup("WORD");
	tab[ASSIGNMENT_WORD] = ft_strdup("ASSIGNMENT_WORD");
	tab[NEWLINE] = ft_strdup("NEWLINE");
	tab[IO_NUMBER] = ft_strdup("IO_NUMBER");
	tab[AND_IF] = ft_strdup("AND_IF");
	tab[AMP] = ft_strdup("AMP");
	tab[OR_IF] = ft_strdup("OR_IF");
	tab[PIPE] = ft_strdup("PIPE");
	tab[SEMI] = ft_strdup("SEMI");
	tab[LESS] = ft_strdup("LESS");
	tab[DLESS] = ft_strdup("DLESS");
	tab[GREAT] = ft_strdup("GREAT");
	tab[DGREAT] = ft_strdup("DGREAT");
	tab[LESSAND] = ft_strdup("LESSAND");
	tab[GREATAND] = ft_strdup("GREATAND");
	tab[DLESSDASH] = ft_strdup("DLESSDASH");
	tab[DLESSDASH + 1] = NULL;
	return (tab);
}

void		print_debug(t_list *elem)
{
	t_token *token;
	char	**tab;
	char	*nl;

	tab = token_debug_init();
	token = elem->data;
	if (token->type == NEWLINE)
		ft_dprintf(cfg_shell()->debug, "str=%10.10s\ttype= %15s\n",
		"\\n", "NEWLINE");
	else
	{
		ft_dprintf(cfg_shell()->debug, "str=%30s\ttype= %15s\t%p\n",
		(nl = escape_nl(token->str)), tab[token->type], token);
		ft_strdel(&nl);
	}
	tabfree(tab);
}
