#include "exec.h"
#include "line_edition.h"
#include "libft.h"
#include <struct.h>
#include <sh.h>
#include "ft_printf.h"
#include "get_next_line.h"
#include "var.h"

void	exec_hist(char *file)
{
	char	*cmd;
	int		fd;

	if (file && (fd = open(file, O_RDONLY)) >= 0)
	{
		protect_fd(1);
		while (get_next_line(fd, &cmd) > 0)
		{
			ft_dprintf(STDERR_FILENO, "%s\n", cmd);
			if (fc_exec_cmd(cmd) <= 0)
				break ;
		}
		protect_fd(0);
		close(fd);
	}
}

int		fc_exec_cmd(char *cmd)
{
	t_lexer		lexer;
	t_parser	parser;
	char		*hist_cmd;
	int			ret;

	ret = 0;
	if (cmd && (hist_cmd = ft_strdup(cmd)))
	{
		if ((ret = lexer_routine(&cmd, &lexer)) <= 0
				|| (ret = parser_routine(&lexer, &parser)) <= 0
				|| (ret = eval_routine(&parser)) <= 0)
		{
			ft_strdel(&hist_cmd);
			return (ret);
		}
		fc_hist_add(hist_cmd);
	}
	return (ret);
}

void	fc_hist_add(char *hist_cmd)
{
	char	*nb;

	if (hist_cmd && ft_atoi(find_var_value(cfg_shell()->sp, "?")) == 0)
	{
		nb = ft_itoa(cfg_shell()->hist_nb);
		if (ft_strcmp(ft_hash_lookup(cfg_shell()->hist_map, nb),
					hist_cmd) != 0)
		{
			ft_strdel(&nb);
			cfg_shell()->hist_nb += 1;
			nb = ft_itoa(cfg_shell()->hist_nb);
			ft_dlstaddtail(&cfg_shell()->history, ft_dlstnew(hist_cmd,
						0));
			ft_hash_add(cfg_shell()->hist_map, nb, ft_strdup(hist_cmd),
					NULL);
		}
		else
			ft_strdel(&hist_cmd);
		ft_strdel(&nb);
	}
	else
		ft_strdel(&hist_cmd);
}
