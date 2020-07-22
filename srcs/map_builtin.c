#include "libft.h"
#include "exec.h"
#include "sh.h"

static	void	feed_tab_value(int *tabi)
{
	tabi[0] = B_ECHO;
	tabi[1] = B_CD;
	tabi[2] = B_SET;
	tabi[3] = B_UNSET;
	tabi[4] = B_HASH;
	tabi[5] = B_EXIT;
	tabi[6] = B_JOBS;
	tabi[7] = B_FG;
	tabi[8] = B_BG;
	tabi[9] = B_TYPE;
	tabi[10] = B_EXPORT;
	tabi[11] = B_ALIAS;
	tabi[12] = B_UNALIAS;
	tabi[13] = B_TEST;
	tabi[14] = B_FC;
}

static	void	feed_tab_key(char **tabi)
{
	tabi[0] = "echo";
	tabi[1] = "cd";
	tabi[2] = "set";
	tabi[3] = "unset";
	tabi[4] = "hash";
	tabi[5] = "exit";
	tabi[6] = "jobs";
	tabi[7] = "fg";
	tabi[8] = "bg";
	tabi[9] = "type";
	tabi[10] = "export";
	tabi[11] = "alias";
	tabi[12] = "unalias";
	tabi[13] = "test";
	tabi[14] = "fc";
}

void			init_builtin_map(t_hash_map *map)
{
	uint8_t		i;
	int32_t		*value;
	int32_t		tab_value[15];
	char		*tab_key[15];

	i = 0;
	feed_tab_value(tab_value);
	feed_tab_key(tab_key);
	while (i < 15)
	{
		value = ft_memalloc(sizeof(int32_t));
		protect_malloc(value);
		ft_hash_add(map, tab_key[i],
				ft_memcpy(value, &tab_value[i], sizeof(int32_t)), free);
		i++;
	}
}
