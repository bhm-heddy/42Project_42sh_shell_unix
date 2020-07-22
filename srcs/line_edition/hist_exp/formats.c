#include "line_edition.h"
#include "ft_printf.h"
#include "analyzer.h"
#include "sh.h"

int		exp_last_cmd(char **src, t_exp *exp)
{
	char	*res;
	char	*val;

	*src += 1;
	if (!(val = ft_itoa(cfg_shell()->hist_nb - 1)))
		ft_ex(EXMALLOC);
	if (!(exp->word = ft_strdup("!")))
		ft_ex(EXMALLOC);
	if (!(res = ft_hash_lookup(cfg_shell()->hist_map, val)))
	{
		ft_strdel(&val);
		return (0);
	}
	ft_strdel(&val);
	exp_substitute(exp, res);
	return (1);
}

int		exp_digit(char **src, t_exp *exp)
{
	int		val;
	char	*res;

	val = ft_atoi(*src);
	while (ft_isdigit(**src))
		*src += 1;
	if (!(exp->word = ft_itoa(val)))
		ft_ex(EXMALLOC);
	if (val < 1 || val >= cfg_shell()->hist_nb)
		return (0);
	if (!(res = ft_hash_lookup(cfg_shell()->hist_map, exp->word)))
		return (0);
	exp_substitute(exp, res);
	return (1);
}

int		exp_minus(char **src, t_exp *exp)
{
	int		histsize;
	int		val;
	char	*res;

	val = ft_atoi(*src);
	*src += 1;
	while (ft_isdigit(**src))
		*src += 1;
	histsize = cfg_shell()->hist_nb;
	if (!(exp->word = ft_itoa(val)))
		ft_ex(EXMALLOC);
	if (val >= 0 || histsize + val < 1)
		return (0);
	val += histsize;
	if (!(exp->param = ft_itoa(val)))
		ft_ex(EXMALLOC);
	if (!(res = ft_hash_lookup(cfg_shell()->hist_map, exp->param)))
		return (0);
	exp_substitute(exp, res);
	return (1);
}

int		exp_word(char **src, t_exp *exp)
{
	int		index;
	char	*res;
	char	*str;

	str = *src;
	while (!ft_strchr(" \t\n", *str) && !ft_strchr(HIST_DELIM, *str))
		exp_add_to_buf(exp, &str, &exp->word);
	*src = str;
	exp_flush_buf(exp, &exp->word);
	index = cfg_shell()->hist_nb;
	while (index)
	{
		if (!(str = ft_itoa(index)))
			ft_ex(EXMALLOC);
		if (!(res = ft_hash_lookup(cfg_shell()->hist_map, str)))
			return (0);
		ft_strdel(&str);
		if (ft_strnequ(res, exp->word, ft_strlen(exp->word)))
		{
			exp_substitute(exp, res);
			return (1);
		}
		index--;
	}
	return (0);
}
