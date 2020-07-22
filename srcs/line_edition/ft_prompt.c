#include "ft_printf.h"
#include <termios.h>
#include <term.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "line_edition.h"
#include <time.h>
#include <stdio.h>
#include "struct.h"
#include "sh.h"
#include "get_next_line.h"
#include <sys/ioctl.h>
#include <signal.h>

static int		init_fd_nonint(t_cfg *cfg)
{
	int	fd;

	fd = -1;
	if (cfg && (fd = open(cfg->file, O_RDONLY)) < 0)
		ft_ex("Bad file descriptor\n");
	if (dup2(fd, 259) == -1)
		ft_ex(EX);
	close(fd);
	fd = 259;
	return (fd);
}

char			*read_nonint(t_cfg *cfg)
{
	char		*line;
	static int	fd = -2;
	int			ret;
	char		*tmp;

	tmp = NULL;
	line = ft_strnew(0);
	if (cfg)
	{
		fd = (fd == -2 ? init_fd_nonint(cfg) : fd);
		ft_strdel(&line);
		if ((ret = get_next_line(fd, &line)) < 0)
			ft_ex("An error occured while reading file\n");
		else if (ret == 0)
			line = ft_strnew(0);
		if (ret > 0)
		{
			if (ft_asprintf(&tmp, "%s\n", line) == -1)
				ft_ex(EXMALLOC);
			ft_strdel(&line);
			line = tmp;
		}
	}
	return (line);
}

void			read_input(void)
{
	int			len;
	int			stop;
	char		buf[9];
	t_cs_line	*cs;

	stop = 0;
	cs = cs_master(NULL, 0);
	if (cs->history)
		cs->history->data = cs->input;
	while (stop >= 0)
	{
		len = read(cs->tty, buf, READ_SIZE);
		if (cs->sig_int)
			break ;
		if (len < 0)
			stop = -1;
		else
			buf[len] = '\0';
		if (cs->history)
			cs->history->data = cs->input;
		cs->read_error = (len < 0 ? 1 : 0);
		stop = (stop >= 0 ? check_keys(buf) : stop);
	}
}

char			*get_cmd_line(t_cs_line *cs, t_dlist *hs)
{
	char	*ret;

	signal(SIGINT, sig_handler);
	ret = NULL;
	read_input();
	if (cs->read_error == 1)
		return (ft_strnew(0));
	end_key(cs);
	if (!cs->sig_int)
		tputs(tgoto(tgetstr("cm", NULL), 0, cs->row + (cs->sig_eof ? 1 : 0)),
				1, &my_putchar);
	term_init(0, NULL);
	if (cs->input && !cs->sig_int && cs->input[0]
		&& !ft_strcheck(cs->input, " \t") && ft_strcmp(cs->input, "\n") != 0
		&& (ret = ft_strdup(cs->input)) >= 0)
		update_history(hs);
	else
	{
		while (cs->history && cs->history->next)
			cs->history = cs->history->next;
		ft_dlstdelone(&cs->history);
	}
	return (!ret && !cs->sig_int && !cs->sig_eof ? ft_strdup("\n") : ret);
}

char			*ft_prompt(char *prompt, char *color)
{
	char		*ret;
	t_cs_line	*cs;
	t_dlist		*hs;
	t_cfg		*cfg;

	ret = NULL;
	cs = NULL;
	if (!(cfg = cfg_shell()))
		return (NULL);
	if (!cfg->interactive)
		return (read_nonint(cfg));
	signal(SIGINT, SIG_IGN);
	signal(SIGWINCH, SIG_IGN);
	signal(SIGTERM, sigterm_handler);
	if (!(term_init(1, prompt) == 1 && (cs = cs_master(NULL, 0))))
		return (NULL);
	cs->prompt_color = color;
	print_prompt(cs);
	hs = cfg->history;
	cs->history = ft_dlstnew(cs->input, 1);
	ft_dlstaddtail(&hs, cs->history);
	ret = get_cmd_line(cs, hs);
	set_signal_ign();
	return ((cs && cs->sig_eof) ? ft_strnew(0) : ret);
}
