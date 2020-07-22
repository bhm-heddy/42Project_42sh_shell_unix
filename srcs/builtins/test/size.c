#include "sh.h"
#include <sys/types.h>
#include <sys/stat.h>

uint8_t		test_size_file(char *path)
{
	struct stat buf;

	if (lstat(path, &buf))
		return (FAILURE);
	return ((buf.st_size > 0) ? 0 : 1);
}
