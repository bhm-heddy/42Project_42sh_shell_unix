#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "sh.h"

int		count_nl(char *src)
{
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	while (src[i])
	{
		if (src[i] == '\n')
			cnt++;
		i++;
	}
	return (cnt);
}

char	*escape_nl(char *src)
{
	char	*str;
	int		cnt;
	int		i;
	int		j;

	if (!src)
		return (NULL);
	i = 0;
	j = 0;
	cnt = count_nl(src);
	str = ft_strnew(ft_strlen(src) + cnt);
	while (src[i])
	{
		if (src[i] == '\n')
		{
			str[j++] = '\\';
			str[j++] = 'n';
			i++;
		}
		else
			str[j++] = src[i++];
	}
	str[j] = '\0';
	return (str);
}

void	print_flag_queue(t_list *elem)
{
	t_lexer_flag	*flag;

	flag = (t_lexer_flag *)elem->data;
	ft_dprintf(cfg_shell()->debug, "%d\t%.8b\n", *flag, *flag);
}

char	*get_flag_name(t_lexer_flag flag)
{
	if (flag == F_BLANK)
		return (ft_strdup(""));
	else if (flag == F_DQUOTE)
		return (ft_strdup("F_DQUOTE"));
	else if (flag == F_SQUOTE)
		return (ft_strdup("F_SQUOTE"));
	else if (flag == F_BSLASH)
		return (ft_strdup("F_BSLASH"));
	else if (flag == F_BRACKEXP)
		return (ft_strdup("F_BRACKEXP"));
	return (NULL);
}

char	*get_state_str(t_lexer *lexer)
{
	if (lexer->state == S_TK_START)
		return (ft_strdup("S_TK_START"));
	else if (lexer->state == S_HD_BODY)
		return (ft_strdup("S_HD_BODY"));
	else if (lexer->state == S_AMP_PIPE)
		return (ft_strdup("S_AMP_PIPE"));
	else if (lexer->state == S_TK_REDIR)
		return (ft_strdup("S_TK_REDIR"));
	else if (lexer->state == S_EXP)
		return (ft_strdup("S_EXP"));
	else if (lexer->state == S_TK_WORD)
		return (ft_strdup("S_TK_WORD"));
	else if (lexer->state == S_IO_NUMBER)
		return (ft_strdup("S_IO_NUMBER"));
	else if (lexer->state == S_FLAG)
		return (ft_strdup("S_FLAG"));
	return (NULL);
}
