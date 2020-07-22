#include "sh.h"
#include <sys/types.h>
#include <sys/stat.h>

uint8_t		test_symlink_file(char *path)
{
	struct stat buf;

	if (stat(path, &buf))
		return (FAILURE);
	return (((buf.st_mode & S_IFMT) == S_IFLNK) ? 0 : 1);
}
