#include "line_edition.h"
#include "ft_printf.h"
#include "analyzer.h"
#include "sh.h"
#include "var.h"

static int		parse_hist_exp(char **src, t_exp *exp)
{
	char	*str;
	int		ret;

	str = *src;
	if (*str == '!')
		ret = exp_last_cmd(src, exp);
	else if (ft_isdigit(*str))
		ret = exp_digit(src, exp);
	else if (*str == '-')
		ret = exp_minus(src, exp);
	else
		ret = exp_word(src, exp);
	if (ret)
		ft_strdel(&exp->word);
	return (ret);
}

static int		handle_exp_flag(char **src, t_exp *exp, int *flag)
{
	char	*str;

	str = *src;
	if (ft_strchr(" \t\n", *(str + 1)))
	{
		exp_add_to_buf(exp, src, &exp->res);
		return (1);
	}
	if (!ft_strchr(HIST_DELIM, *(str + 1)))
	{
		(*src)++;
		exp_flush_buf(exp, &exp->res);
		*flag = 1;
		return (parse_hist_exp(src, exp));
	}
	exp_add_to_buf(exp, src, &exp->res);
	return (1);
}

static int		hist_exp_error(t_exp *exp, char **line)
{
	t_cfg	*shell;
	char	*hist_nb;
	t_dlist	*dlst;

	shell = cfg_shell();
	dlst = shell->history;
	if (!(hist_nb = ft_itoa(shell->hist_nb)))
		ft_ex(EXMALLOC);
	ft_dprintf(2, "%s: !%s: event not found\n", PROJECT, exp->word);
	free_exp_content(exp);
	ft_setvar(&shell->sp, "?", "127");
	ft_hash_delone(shell->hist_map, hist_nb, free);
	while (dlst->next)
		dlst = dlst->next;
	if (dlst && dlst->prev)
	{
		dlst->prev->next = NULL;
		ft_dlstdelone(&dlst);
	}
	shell->hist_nb--;
	if (!shell->interactive)
		exit_routine(shell, 127);
	ft_strdel(line);
	ft_strdel(&hist_nb);
	return (0);
}

static void		history_update(char *line)
{
	t_cfg	*shell;
	char	*hist_nb;
	t_dlist	*dlst;
	char	*res;

	shell = cfg_shell();
	if (!(hist_nb = ft_itoa(shell->hist_nb)))
		ft_ex(EXMALLOC);
	if (!(res = ft_strdup(line)))
		ft_ex(EXMALLOC);
	res[ft_strlen(res) - 1] = 0;
	ft_hash_add(shell->hist_map, hist_nb, res, free);
	free(hist_nb);
	dlst = shell->history;
	while (dlst->next)
		dlst = dlst->next;
	if (!(res = ft_strdup(line)))
		ft_ex(EXMALLOC);
	res[ft_strlen(res) - 1] = 0;
	free(dlst->data);
	dlst->data = res;
}

int				expand_history(char **line)
{
	char	*str;
	t_exp	exp;
	int		flag;

	flag = 0;
	str = *line;
	init_exp(&exp);
	while (*str)
	{
		if (*str == '!' && !handle_exp_flag(&str, &exp, &flag))
			return (hist_exp_error(&exp, line));
		exp_add_to_buf(&exp, &str, &exp.res);
	}
	exp_flush_buf(&exp, &exp.res);
	ft_strdel(line);
	if (!(*line = ft_strdup(exp.res)))
		ft_ex(EXMALLOC);
	if (flag)
	{
		history_update(exp.res);
		ft_printf("%s", exp.res);
	}
	free_exp_content(&exp);
	return (1);
}
