#include "analyzer.h"
#include "sh.h"
#include "libft.h"
#include "var.h"
#include "ft_printf.h"

char	*resolve_parameter(char *str, int hash)
{
	char	*res;
	int		type;

	type = 0;
	if ((((!hash && ft_strlen(str) == 1) || (hash && ft_strlen(str) == 2))
	&& ft_strchr("@*#?-$!", *str)) || ft_isdigit(*str))
		type = 1;
	else if (!ft_isname(str) && !(hash && *str == '#' && ft_isname(str + 1)))
		return (NULL);
	if ((res = exp_getenv(str, type, hash))
	&& !(res = ft_strdup(res)))
		ft_ex("Cannot allocate memory\n");
	if (!res && !(res = ft_strnew(0)))
		ft_ex("Cannot allocate memory\n");
	return (res);
}

int		resolve_colon_param(char **str, t_exp *exp, char *param)
{
	int		ret;

	(*str)++;
	if (!ft_strchr("-=?+", **str)
	|| !(exp->param = resolve_parameter(param, 0)))
		return (-1);
	if (exp->param[0])
	{
		if (**str == '+')
			ret = substitute_word(exp, str);
		else
			ret = substitute_parameter(exp, str);
	}
	else if (**str == '-')
		ret = substitute_word(exp, str);
	else if (**str == '=')
		ret = assign_word(exp, str, param);
	else if (**str == '?')
		ret = print_error_parameter(exp, str, param);
	else
		ret = substitute_null(exp, str);
	ft_strdel(&exp->param);
	ft_strdel(&exp->word);
	return (ret);
}

int		resolve_brace_param(char **str, t_exp *exp, char *param)
{
	int		hash;
	char	*hashparam;

	(*str)++;
	hash = *param == '#' ? 1 : 0;
	if (!param || !*param)
		return (-1);
	if (!(exp->param = resolve_parameter(param, hash)))
		return (-1);
	if (hash)
	{
		if (!(hashparam = ft_itoa(ft_strlen(exp->param))))
			ft_ex("Cannot allocate memory\n");
		exp_substitute(exp, hashparam);
		ft_strdel(&hashparam);
	}
	else
		exp_substitute(exp, exp->param);
	ft_strdel(&exp->param);
	return (1);
}

int		resolve_pattern_param(char **str, t_exp *exp, char *param)
{
	int	type;
	int	ret;

	ret = -1;
	type = **str == '#' ? 0 : 1;
	(*str)++;
	if ((!type && **str == '#') || (type && **str == '%'))
		(*str)++;
	if (!(exp->param = resolve_parameter(param, 0))
	|| (ret = rec_word_parse(exp, str)) < 0
	|| (ret = exp_main(&exp->word, exp->assign)) < 0)
		return (ret);
	exp->word = (void *)a_quote_removal((char **)&exp->word);
	if (**str == '}')
		(*str)++;
	substitute_pattern(exp, type);
	ft_strdel(&exp->param);
	ft_strdel(&exp->word);
	return (1);
}
