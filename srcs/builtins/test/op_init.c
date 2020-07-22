#include "libft.h"
#include "struct.h"
#include "exec.h"
#include "sh.h"
#include "ft_printf.h"
#include "var.h"

void	test_init_un_op(void)
{
	t_hash_map	*map;

	if (!(map = ft_hash_init(20)))
		ft_ex(EXMALLOC);
	cfg_shell()->test_un = map;
	ft_hash_add(map, "-b", test_bloc_file, NULL);
	ft_hash_add(map, "-c", test_char_file, NULL);
	ft_hash_add(map, "-d", test_dir_file, NULL);
	ft_hash_add(map, "-x", test_exec_file, NULL);
	ft_hash_add(map, "-p", test_fifo_file, NULL);
	ft_hash_add(map, "-e", test_entry_file, NULL);
	ft_hash_add(map, "-r", test_read_file, NULL);
	ft_hash_add(map, "-f", test_regular_file, NULL);
	ft_hash_add(map, "-g", test_setgid_file, NULL);
	ft_hash_add(map, "-u", test_setuid_file, NULL);
	ft_hash_add(map, "-s", test_size_file, NULL);
	ft_hash_add(map, "-S", test_socket_file, NULL);
	ft_hash_add(map, "-L", test_symlink_file, NULL);
	ft_hash_add(map, "-h", test_symlink_file, NULL);
	ft_hash_add(map, "-w", test_write_file, NULL);
	ft_hash_add(map, "-z", test_len_string, NULL);
}

void	test_init_bin_op(void)
{
	t_hash_map	*map;

	if (!(map = ft_hash_init(10)))
		ft_ex(EXMALLOC);
	cfg_shell()->test_bin = map;
	ft_hash_add(map, "-eq", test_equal_int, NULL);
	ft_hash_add(map, "-ne", test_diff_int, NULL);
	ft_hash_add(map, "-gt", test_greater_int, NULL);
	ft_hash_add(map, "-ge", test_greator_int, NULL);
	ft_hash_add(map, "-lt", test_lesser_int, NULL);
	ft_hash_add(map, "-le", test_lessor_int, NULL);
	ft_hash_add(map, "=", test_equal_string, NULL);
	ft_hash_add(map, "!=", test_diff_string, NULL);
}

void	init_test_op(void)
{
	test_init_un_op();
	test_init_bin_op();
}
