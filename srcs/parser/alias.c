#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "var.h"
#include "sh.h"
#include "exec.h"

void			reset_alias_list(void)
{
	t_list	*src;

	src = cfg_shell()->alias;
	ft_lstdel(&cfg_shell()->alias_cpy, unsetvar_del);
	if (!(cfg_shell()->alias_cpy = ft_lstdup(src, sizeof(t_var), cpy_var_list)))
		ft_ex(EXMALLOC);
}

static t_var	*remove_alias_item(t_list **alias_lst, char *name)
{
	t_list	*res;
	t_list	*tmp;
	t_var	*var;

	if (!(res = *alias_lst))
		return (0);
	var = res->data;
	if (ft_strequ(var->ctab[0], name))
	{
		*alias_lst = res->next;
		free(res);
		return (var);
	}
	while (res->next && (((var = res->next->data)) || TRUE))
	{
		if (ft_strequ(var->ctab[0], name))
		{
			tmp = res->next;
			res->next = res->next->next;
			free(tmp);
			return (var);
		}
		res = res->next;
	}
	return (NULL);
}

char			get_last_char(char *str)
{
	int		i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
		i++;
	return (str[--i]);
}

int				p_expand_alias(t_token *token, t_parser *parser)
{
	t_var	*cpy;
	t_lexer	lexer;
	int		(*table_builder[10][17])(t_token *, t_parser *);
	int		rec_flag;

	rec_flag = 0;
	if (!cfg_shell()->alias_rec && (rec_flag = 1))
		cfg_shell()->alias_rec = 1;
	ft_bzero(&lexer, sizeof(t_lexer));
	if (!(cpy = remove_alias_item(&cfg_shell()->alias_cpy, token->str)))
		return (0);
	ft_lexer(&cpy->ctab[1], &lexer);
	p_init_state_machine(table_builder);
	p_tokeniter(lexer.token_lst, parser, table_builder);
	ft_lstdel(&lexer.token_lst, del_token);
	parser->space_flag = 0;
	if (ft_strchr(" \t", get_last_char(cpy->ctab[1])))
		parser->space_flag = 1;
	if (rec_flag && !(cfg_shell()->alias_rec = 0))
		reset_alias_list();
	del_struct_tvar(cpy, sizeof(t_var));
	return (1);
}
