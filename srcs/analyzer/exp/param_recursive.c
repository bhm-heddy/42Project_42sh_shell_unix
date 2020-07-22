#include "analyzer.h"
#include "libft.h"

int	rec_param_dispatch(char **str, t_exp *exp, char **param)
{
	int		ret;

	ret = 0;
	if (**str == '#' && !exp->i)
		return (0);
	else if (**str == ':')
	{
		exp_flush_buf(exp, param);
		ret = resolve_colon_param(str, exp, *param);
		ft_strdel(param);
	}
	else if (**str == '}')
	{
		exp_flush_buf(exp, param);
		ret = resolve_brace_param(str, exp, *param);
		ft_strdel(param);
	}
	else if (ft_strchr("#%", **str))
	{
		exp_flush_buf(exp, param);
		ret = resolve_pattern_param(str, exp, *param);
		ft_strdel(param);
	}
	return (ret);
}

int	rec_param_exp(t_exp *exp, char **str)
{
	char	*param;
	int		ret;

	*str = *str + 2;
	param = NULL;
	ret = 0;
	while (**str)
	{
		if (!exp->bs && ft_strchr(":}%#", **str)
		&& (ret = rec_param_dispatch(str, exp, &param)))
			break ;
		exp_add_to_buf(exp, str, &param);
		if (exp->bs)
			exp->bs--;
	}
	ft_strdel(&param);
	if (!ret)
		return (-1);
	return (ret);
}
