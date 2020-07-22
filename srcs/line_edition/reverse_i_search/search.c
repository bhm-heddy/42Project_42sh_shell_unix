#include "libft.h"
#include "line_edition.h"
#include "struct.h"
#include "ft_printf.h"
#include "sh.h"

void	get_hist_elem(t_dlist **hist, char **input, char *caps)
{
	char	*tmp;

	if (input && *input)
	{
		tmp = *input;
		ft_asprintf(input, "%s%s", tmp, caps);
		ft_strdel(&tmp);
	}
	else
		*input = ft_strdup(caps);
	if (!hist || !*hist || !(*hist)->prev || !(*hist)->data)
	{
		*hist = cfg_shell()->history;
		while ((*hist)->next)
			*hist = (*hist)->next;
	}
	while ((*hist)->prev && !ft_strstr((char *)(*hist)->data, *input))
		(*hist) = (*hist)->prev;
}

int		history_search(t_cs_line *cs, char *caps)
{
	static char		*input = NULL;
	static t_dlist	*hist = NULL;

	if (cs && caps && ft_strcmp(caps, "\n") != 0 && !cs->sig_int)
	{
		if (caps[0] == (char)127)
			return (del_char(&input, hist, cs));
		get_hist_elem(&hist, &input, caps);
		ft_clear(1);
		print_prompt(cs);
		ft_dprintf(cs->tty, "\"%s\" : %s", input, (char *)hist->data);
	}
	else if (cs)
	{
		ctrl_r_off(cs, caps);
		ft_strdel(&input);
		if (hist && hist->data && !cs->sig_int && !cs->sig_eof)
		{
			ft_strdel(&cs->input);
			cs->input = ft_strdup((char *)hist->data);
		}
		hist = NULL;
	}
	return (0);
}
