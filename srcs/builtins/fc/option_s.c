#include "exec.h"
#include "line_edition.h"
#include "libft.h"
#include <struct.h>
#include <sh.h>
#include "ft_printf.h"
#include "get_next_line.h"
#include "var.h"

char	*get_cmd_by_oc(t_cfg *cfg, char *av)
{
	int		i;
	int		n;
	t_dlist	*hs;
	char	*cmd;

	hs = NULL;
	cmd = NULL;
	if (av && (hs = cfg->history))
	{
		while (hs->next)
			hs = hs->next;
		n = ft_strlen(av);
		while (hs->prev)
		{
			i = 0;
			while (hs->data && ((char *)hs->data)[i]
					&& ((char *)hs->data)[i] == ' ')
				i++;
			if (hs->data && ft_strnstr(&((char *)hs->data)[i], av, n))
				return (ft_strdup((char *)hs->data));
			hs = hs->prev;
		}
	}
	return (cmd);
}

char	*get_cmd_by_num(t_cfg *cfg, char *av)
{
	int		n;
	char	*cmd;
	char	*nb;

	cmd = NULL;
	if (av)
	{
		n = ft_atoi(av);
		n = (n < 0 ? cfg->hist_nb + n : n);
		nb = ft_itoa(n + 1);
		cmd = ft_strdup((char *)ft_hash_lookup(cfg->hist_map, nb));
		ft_strdel(&nb);
	}
	return (cmd);
}

char	*get_hist_cmd(char *av, t_cfg *cfg)
{
	char	*cmd;
	char	*nb;

	cmd = NULL;
	if (av)
	{
		if (ft_strisdigit(av))
			return (get_cmd_by_num(cfg, av));
		else
			return (get_cmd_by_oc(cfg, av));
	}
	else
	{
		nb = ft_itoa(cfg->hist_nb);
		cmd = ft_strdup((char *)ft_hash_lookup(cfg->hist_map, nb));
		ft_strdel(&nb);
	}
	return (cmd);
}

void	get_pattern(char **av, int *ac, char **old, char **new)
{
	char	*oc;

	if (av[*ac] && (oc = ft_strchr(av[*ac], '=')))
	{
		*oc = '\0';
		*old = av[*ac];
		*new = oc + 1;
		(void)*ac++;
	}
}

void	reexecute_cmd(char **av, int ac)
{
	char	*old;
	char	*new;
	char	*oc;
	char	*cmd;

	old = NULL;
	new = NULL;
	get_pattern(av, &ac, &old, &new);
	if ((cmd = get_hist_cmd(av[ac], cfg_shell())))
	{
		if (old)
		{
			oc = cmd;
			cmd = ft_strrep(cmd, old, new);
			ft_strdel(&oc);
		}
		oc = get_histfilename();
		if (!oc || (ac = open(oc, O_CREAT | O_WRONLY, 0666)) < 0)
			return ;
		ft_dprintf(ac, "%s", cmd);
		ft_strdel(&cmd);
		close(ac);
		exec_hist(oc);
		ft_strdel(&oc);
	}
}
