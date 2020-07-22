#include "ft_printf.h"

int	fc_usage(void)
{
	char	*usage;
	char	*usage2;

	usage = " : fc [-r][-e editor] [first[last]]\n        ";
	usage2 = "fc -l[-nr] [first[last]]\n        fc -s[old=new] [first]\n";
	ft_dprintf(2, "usage%s%s", usage, usage2);
	return (-1);
}

int	fc_bad_option(char *s)
{
	ft_dprintf(2, "fc : invallid option --%s\n", s);
	fc_usage();
	return (-1);
}

int	fc_bad_usage(char *s)
{
	ft_dprintf(2, "fc : bad usage -%s\n", s);
	fc_usage();
	return (-1);
}

int	fc_missing_arg(void)
{
	ft_dprintf(2, "fc : missing argument after option -e\n");
	fc_usage();
	return (-1);
}

int	range_error(void)
{
	ft_printf("fc : history specification out of range");
	return (-1);
}
