#include "libft.h"
#include "ft_printf.h"
#include "lexer.h"
#include "sh.h"

void	del_flag_queue(void *data, size_t size)
{
	(void)size;
	ft_memdel(&data);
}

void	del_token(void *data, size_t size)
{
	t_token	*token;

	(void)size;
	token = (t_token *)data;
	ft_strdel(&token->str);
	free(data);
}

void	tabfree(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
}

void	del_str(void *data, size_t size)
{
	(void)size;
	free(data);
}
