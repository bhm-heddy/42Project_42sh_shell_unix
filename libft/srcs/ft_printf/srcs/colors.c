#include "ft_printf.h"

static int	conv_red_green(t_printf *data, int *len)
{
	if (ft_strnequ(data->fmt, "{green}", (*len = 7)))
		buffer(C_GREEN, data, data->printed);
	else if (ft_strnequ(data->fmt, "{GREEN}", (*len = 7)))
		buffer(C_BGREEN, data, data->printed);
	else if (ft_strnequ(data->fmt, "{red}", (*len = 5)))
		buffer(C_RED, data, data->printed);
	else if (ft_strnequ(data->fmt, "{RED}", (*len = 5)))
		buffer(C_BRED, data, data->printed);
	else
		return (0);
	return (1);
}

static int	conv_yellow_blue(t_printf *data, int *len)
{
	if (ft_strnequ(data->fmt, "{yellow}", (*len = 8)))
		buffer(C_YELLOW, data, data->printed);
	else if (ft_strnequ(data->fmt, "{YELLOW}", (*len = 8)))
		buffer(C_BYELLOW, data, data->printed);
	else if (ft_strnequ(data->fmt, "{blue}", (*len = 6)))
		buffer(C_BLUE, data, data->printed);
	else if (ft_strnequ(data->fmt, "{BLUE}", (*len = 6)))
		buffer(C_BBLUE, data, data->printed);
	else
		return (0);
	return (1);
}

static int	conv_magenta_cyan(t_printf *data, int *len)
{
	if (ft_strnequ(data->fmt, "{magenta}", (*len = 9)))
		buffer(C_MAGENTA, data, data->printed);
	else if (ft_strnequ(data->fmt, "{MAGENTA}", (*len = 9)))
		buffer(C_BMAGENTA, data, data->printed);
	else if (ft_strnequ(data->fmt, "{cyan}", (*len = 6)))
		buffer(C_CYAN, data, data->printed);
	else if (ft_strnequ(data->fmt, "{CYAN}", (*len = 6)))
		buffer(C_BCYAN, data, data->printed);
	else
		return (0);
	return (1);
}

static int	conv_eoc(t_printf *data, int *len)
{
	if (ft_strnequ(data->fmt, "{eoc}", (*len = 5)))
		buffer(C_EOC, data, (data->printed = 4));
	else
		return (0);
	return (1);
}

void		conv_color(t_printf *data)
{
	int		len;

	len = 0;
	data->printed = 7;
	if (ft_strchr("gGrR", *(data->fmt + 1))
	&& !conv_red_green(data, &len))
		buffer("{", data, 1);
	else if (ft_strchr("yYbB", *(data->fmt + 1))
	&& !conv_yellow_blue(data, &len))
		buffer("{", data, 1);
	else if (ft_strchr("mMcC", *(data->fmt + 1))
	&& !conv_magenta_cyan(data, &len))
		buffer("{", data, 1);
	else if (*(data->fmt + 1) == 'e'
	&& !conv_eoc(data, &len))
		buffer("{", data, 1);
	else if (len)
	{
		data->ret += data->printed;
		data->fmt += len - 1;
		return ;
	}
	else
		buffer("{", data, 1);
}
