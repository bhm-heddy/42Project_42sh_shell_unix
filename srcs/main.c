#include "libft.h"
#include "sh.h"
#include "var.h"
#include "job_control.h"

t_cfg	*cfg_shell(void)
{
	static t_cfg shell;

	return (&shell);
}

int		main(int ac, char **av, char **env)
{
	int			ret;
	char		*line;
	t_lexer		lexer;
	t_parser	parser;
	t_cfg		*shell;

	shell = init_shell(env, av, ac);
	while (1)
	{
		build_prompt_ps1(0);
		check_child(cfg_shell(), cfg_shell()->job);
		if (!(ret = line_edition_routine(&line))
		|| !(ret = lexer_routine(&line, &lexer))
		|| !(ret = parser_routine(&lexer, &parser))
		|| !(ret = eval_routine(&parser)))
		{
			if (!ret && !shell->interactive)
				exit_routine(shell, 2);
		}
	}
	exit_routine(shell, ft_atoi(find_var_value(shell->sp, "?")));
}
