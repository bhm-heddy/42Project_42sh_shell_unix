#include "exec.h"
#include "line_edition.h"
#include "libft.h"
#include <struct.h>
#include <sh.h>
#include "ft_printf.h"
#include "get_next_line.h"
#include "var.h"

char	*get_edit_cmd(int8_t *fl, char *hist, char **av, int ac)
{
	char	*cmd;

	if ((cmd = "\0") && hist)
	{
		if (!(*fl & 1) && !find_var_value(cfg_shell()->env, "FCEDIT"))
			ft_asprintf(&cmd, "%s %s", "ed", hist);
		else if (!(*fl & 1))
			ft_asprintf(&cmd, "%s %s", find_var_value(cfg_shell()->env,
						"FCEDIT"), hist);
		else if (av[ac])
			ft_asprintf(&cmd, "%s %s", av[ac], hist);
		else
		{
			fc_missing_arg();
			return (NULL);
		}
	}
	return (cmd);
}

int		editor_launcher(char *cmd)
{
	int			ret;
	t_lexer		lexer;
	t_parser	parser;

	ret = 0;
	if (cmd)
	{
		if ((ret = lexer_routine(&cmd, &lexer)) <= 0
				|| (ret = parser_routine(&lexer, &parser)) <= 0
				|| (ret = eval_routine(&parser)) <= 0)
			return (0);
	}
	return (ret);
}

int		edit_hist(int8_t *fl, char **av, int ac)
{
	char	*hist;
	char	*cmd;

	if ((hist = create_tmphist(fl, av, (av[ac] ? ac + 1 : ac))))
	{
		if (!(cmd = get_edit_cmd(fl, hist, av, ac)) || !editor_launcher(cmd))
		{
			ft_strdel(&hist);
			return (0);
		}
		if (ft_atoi(find_var_value(cfg_shell()->sp, "?")) == 0)
			exec_hist(hist);
		ft_strdel(&hist);
		return (1);
	}
	else
		ft_dprintf(STDERR_FILENO,
				"fc : Could not create temporary file : permission denied.");
	return (0);
}
