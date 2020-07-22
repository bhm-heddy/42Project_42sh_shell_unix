#include "analyzer.h"
#include "libft.h"
#include "sh.h"
#include "var.h"

int		get_tilde_exp(t_exp *exp)
{
	struct passwd	*pwd;

	if (!(pwd = getpwnam(exp->buf)))
		return (0);
	if (exp->res && !(exp->res = ft_strlclnjoin(exp->res, pwd->pw_dir)))
		ft_ex("Cannot allocate memory\n");
	else if (!exp->res && !(exp->res = ft_strdup(pwd->pw_dir)))
		ft_ex("Cannot allocate memory\n");
	return (1);
}

int		get_home_val(t_exp *exp)
{
	char	*tilde;
	char	*var;

	if (!(var = find_var_value(cfg_shell()->env, "HOME"))
	&& !(tilde = ft_strnew(0)))
		ft_ex("Cannot allocate memory\n");
	else if (var && !(tilde = ft_strdup(var)))
		ft_ex("Cannot allocate memory\n");
	if (exp->res && !(exp->res = ft_strlclnjoin(exp->res, tilde)))
		ft_ex("Cannot allocate memory\n");
	else if (!exp->res && !(exp->res = ft_strdup(tilde)))
		ft_ex("Cannot allocate memory\n");
	free(tilde);
	return (1);
}

int		parse_tilde_exp(char **string, t_exp *exp, int assign)
{
	int		i;
	char	*str;

	str = *string;
	i = 1;
	while (str[i])
	{
		if (ft_strchr("\'\"\\", str[i]))
			return (0);
		if (str[i] == '/' || (assign && str[i] == ':'))
			break ;
		exp->buf[exp->i] = str[i];
		i++;
		exp->i++;
	}
	if ((i == 1 && !get_home_val(exp)) || (i > 1 && !get_tilde_exp(exp)))
		return (0);
	ft_bzero(exp->buf, EXP_BSIZE);
	*string = str + i;
	return (1);
}

void	find_tilde_exp(char **word, t_exp exp)
{
	char	*str;
	int		i;

	i = 0;
	if (!word || !*word)
		return ;
	str = *word;
	if (*str != '~' || !(parse_tilde_exp(&str, &exp, 0)))
		return ;
	while (str[i])
	{
		if (exp.i >= EXP_BSIZE - 1)
			exp_flush_buf(&exp, &exp.res);
		exp.buf[exp.i] = *str;
		str++;
		exp.i++;
	}
	exp_flush_buf(&exp, &exp.res);
	free(*word);
	*word = exp.res;
}
