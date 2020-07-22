#include "libft.h"
#include "sh.h"
#include <sys/types.h>
#include <sys/stat.h>

uint8_t		test_entry_file(char *path)
{
	struct stat buf;

	if (lstat(path, &buf))
		return (FAILURE);
	return (SUCCESS);
}
