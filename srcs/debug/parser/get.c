#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "sh.h"

int		get_nb_cmd(t_list *cmd)
{
	int nb;

	nb = 1;
	if (!cmd->data)
		return (0);
	while ((cmd = cmd->next))
		nb++;
	return (nb);
}

int		get_nb_and_or(t_list *and_or)
{
	int nb;

	nb = 1;
	if (!and_or->data)
		return (0);
	while ((and_or = and_or->next))
		nb++;
	return (nb);
}

int		get_nb_word_list(t_list *list)
{
	int nb;

	nb = 1;
	if (!list || !list->data)
		return (0);
	while ((list = list->next))
		nb++;
	return (nb);
}

char	*get_redir_op(t_token_type type)
{
	if (type == 10)
		return (ft_strdup("<"));
	if (type == 11)
		return (ft_strdup("<<"));
	if (type == 12)
		return (ft_strdup(">"));
	if (type == 13)
		return (ft_strdup(">>"));
	if (type == 14)
		return (ft_strdup("<&"));
	if (type == 15)
		return (ft_strdup(">&"));
	if (type == 16)
		return (ft_strdup("<<-"));
	return (NULL);
}

char	*get_and_or_type_str(t_and_or *and_or)
{
	if (and_or->type == AND_IF)
		return (ft_strdup("AND_IF"));
	else if (and_or->type == OR_IF)
		return (ft_strdup("OR_IF"));
	else
		return (NULL);
}
