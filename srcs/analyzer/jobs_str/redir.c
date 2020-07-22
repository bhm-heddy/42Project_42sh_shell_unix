#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "parser.h"
#include "analyzer.h"
#include "var.h"
#include "line_edition.h"
#include "sh.h"

static char		*get_redir_type_str(t_token_type type)
{
	if (type == LESS)
		return (ft_strdup("<"));
	else if (type == DLESS)
		return (ft_strdup("<<"));
	else if (type == GREAT)
		return (ft_strdup(">"));
	else if (type == DGREAT)
		return (ft_strdup(">>"));
	else if (type == LESSAND)
		return (ft_strdup("<&"));
	else if (type == GREATAND)
		return (ft_strdup(">&"));
	else if (type == DLESSDASH)
		return (ft_strdup("<<-"));
	else
		return (ft_strnew(0));
	return (NULL);
}

static char		*get_redir_fmt(t_redir *redir)
{
	char	*str;

	if (!redir->io_num && !(redir->io_num = ft_strdup("")))
		ft_ex(EXMALLOC);
	if (redir->type == DLESS || redir->type == DLESSDASH)
	{
		if (!(str = ft_strdup("%s%s%s\n%s%s\n")))
			ft_ex(EXMALLOC);
	}
	else
	{
		if (!(str = ft_strdup("%s%s%s %s"))
		|| !(redir->delim = ft_strdup("")))
			ft_ex(EXMALLOC);
	}
	return (str);
}

static char		*join_redir_str(t_redir *redir, char **str)
{
	char	*tmp;
	char	*res;
	char	*fmt;

	fmt = NULL;
	tmp = NULL;
	if (!(fmt = get_redir_fmt(redir))
	|| !(tmp = get_redir_type_str(redir->type)))
		ft_ex(EXMALLOC);
	if (ft_asprintf(&res, fmt, redir->io_num, tmp,
	redir->delim, redir->file, redir->delim) == -1)
		ft_ex(EXMALLOC);
	ft_strdel(&fmt);
	ft_strdel(&tmp);
	tmp = res;
	if (str && *str)
	{
		if (ft_asprintf(&res, "%s %s", *str, tmp) == -1)
			ft_ex(EXMALLOC);
		ft_strdel(&tmp);
		ft_strdel(str);
	}
	return (res);
}

char			*get_redir_str(t_list *redir_lst)
{
	t_redir	*redir;
	char	*str;

	if (!redir_lst || !redir_lst->data)
		return (NULL);
	str = NULL;
	while (redir_lst && redir_lst->data)
	{
		redir = (t_redir *)redir_lst->data;
		str = join_redir_str(redir, &str);
		redir_lst = redir_lst->next;
	}
	return (str);
}

char			*get_args_str(char **args)
{
	int		i;
	char	*str;
	char	*tmp;

	if (args && args[0])
	{
		if (!(str = ft_strdup(args[0])))
			ft_ex(EXMALLOC);
	}
	else
		return (0);
	i = 1;
	while (args[i])
	{
		if (ft_asprintf(&tmp, "%s %s", str, args[i]) == -1)
			ft_ex(EXMALLOC);
		ft_strdel(&str);
		str = tmp;
		i++;
	}
	return (str);
}
