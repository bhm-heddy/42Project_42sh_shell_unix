#include "analyzer.h"
#include "sh.h"
#include "libft.h"
#include "var.h"

int		substitute_parameter(t_exp *exp, char **str)
{
	int	ret;

	exp_substitute(exp, exp->param);
	(*str)++;
	ret = skip_word(exp, str);
	if (**str == '}')
		(*str)++;
	return (ret);
}

int		substitute_word(t_exp *exp, char **str)
{
	int	ret;

	(*str)++;
	if ((ret = rec_word_parse(exp, str)) < 0
	|| (ret = exp_main(&exp->word, exp->assign)) < 0)
		return (ret);
	if (**str == '}')
		(*str)++;
	exp_substitute(exp, exp->word);
	return (1);
}

int		assign_word(t_exp *exp, char **str, char *param)
{
	int	ret;

	if (ft_strlen(param) == 1 && (*param == '@' || *param == '*'
	|| *param == '#' || *param == '?' || *param == '-' || *param == '$'
	|| *param == '!' || ft_isdigit(*param)))
	{
		if (substitute_parameter(exp, str) < 0)
			return (-1);
		return (0);
	}
	if ((ret = substitute_word(exp, str)) < 0)
		return (ret);
	ft_setvar(&cfg_shell()->env, param, exp->word);
	return (1);
}

int		substitute_null(t_exp *exp, char **str)
{
	int	ret;

	(*str)++;
	ret = skip_word(exp, str);
	if (**str == '}')
		(*str)++;
	return (ret);
}

void	substitute_pattern(t_exp *exp, int type)
{
	int	plen;
	int	wlen;

	plen = ft_strlen(exp->param);
	wlen = ft_strlen(exp->word);
	if (wlen > plen)
		exp_substitute(exp, exp->param);
	else if (!type && !ft_strncmp(exp->word, exp->param, wlen))
		exp_substitute(exp, exp->param + wlen);
	else if (type && !ft_strcmp(exp->word, exp->param + plen - wlen))
	{
		*(exp->param + plen - wlen) = '\0';
		exp_substitute(exp, exp->param);
	}
	else
		exp_substitute(exp, exp->param);
}
