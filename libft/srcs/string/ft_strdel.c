#include <stdlib.h>

void	ft_strdel(char **as)
{
	if (!(*as) || !as)
		return ;
	free(*as);
	*as = NULL;
}
