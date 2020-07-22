#include "analyzer.h"
#include "libft.h"
#include "ft_printf.h"
#include "sh.h"
#include "var.h"

static int		first_call_exp(t_simple_cmd *cmd)
{
	t_list			*lst;
	int				ret;

	if (cmd->cmd_name && (ret = exp_main(&cmd->cmd_name, 0)) < 0)
		return (ret == -1 ? exp_err(cmd->cmd_name) : -1);
	lst = cmd->args;
	while (lst)
	{
		if ((ret = exp_main((char **)&lst->data, 0)) < 0)
			return (ret == -1 ? exp_err((char *)lst->data) : -1);
		lst = lst->next;
	}
	return (1);
}

static int		second_call_exp(t_simple_cmd *cmd)
{
	t_list			*lst;
	int				ret;
	t_assignment	*assign;
	t_redir			*redir;

	lst = cmd->assign;
	while (lst && (assign = lst->data))
	{
		if ((ret = exp_main(&assign->val, 1)) < 0)
			return (ret == -1 ? exp_err((char *)assign->val) : -1);
		lst = lst->next;
	}
	lst = cmd->redir;
	while (lst && (redir = lst->data))
	{
		if ((ret = exp_main(&redir->file, 1)) < 0)
			return (ret == -1 ? exp_err((char *)redir->file) : -1);
		lst = lst->next;
	}
	return (1);
}

static void		call_quote_removal(t_simple_cmd *cmd)
{
	t_list			*lst;
	t_assignment	*assign;
	t_redir			*redir;

	cmd->cmd_name = (void *)a_quote_removal((char **)&cmd->cmd_name);
	lst = cmd->args;
	while (lst)
	{
		lst->data = (void *)a_quote_removal((char **)&lst->data);
		lst = lst->next;
	}
	lst = cmd->assign;
	while (lst)
	{
		assign = lst->data;
		assign->val = a_quote_removal((char **)&assign->val);
		lst = lst->next;
	}
	lst = cmd->redir;
	while (lst)
	{
		redir = lst->data;
		redir->file = a_quote_removal((char **)&redir->file);
		lst = lst->next;
	}
}

int				word_expansions(t_simple_cmd *cmd)
{
	int				debug;

	if ((debug = cfg_shell()->debug))
		ft_dprintf(debug, "\n----------- expansions -----------\n\n");
	if (first_call_exp(cmd) < 0 || second_call_exp(cmd) < 0)
		return (-1);
	field_splitting(cmd);
	call_quote_removal(cmd);
	return (1);
}

int				exp_main(char **word, int assign)
{
	t_exp		exp;
	int			ret;
	t_cfg		*cfg;

	cfg = cfg_shell();
	if (cfg->debug)
		ft_dprintf(cfg->debug, "Exp main start,\nstr= [%s]\n\n", *word);
	init_exp(&exp);
	exp.assign = assign;
	if (assign)
		find_tilde_exp_assign(word, exp);
	else
		find_tilde_exp(word, exp);
	ft_bzero(exp.buf, EXP_BSIZE);
	if ((ret = parse_param_exp(word, exp)) < 0)
		return (ret);
	if (cfg->debug)
		ft_dprintf(cfg->debug, "Exp main end,\nstr= [%s]\n\n", *word);
	return (1);
}
