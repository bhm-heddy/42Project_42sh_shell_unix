#include "ft_printf.h"

void	init_dispatcher(t_printf *data, void (*disp[11])(t_printf *))
{
	disp[0] = &conv_int;
	disp[1] = &conv_uint;
	disp[2] = &conv_uint;
	disp[3] = &conv_float;
	disp[4] = &conv_uint;
	disp[5] = &conv_char;
	disp[6] = &conv_str;
	disp[7] = &conv_uint;
	disp[8] = &conv_ptr;
	disp[9] = &conv_esc;
	disp[10] = &conv_str;
	data->disp = (void *)disp;
	data->disp_set = 1;
}

int		init_type(t_printf *data, int fd, char **str, int str_n)
{
	data->str = str;
	data->fd = fd;
	data->str_n = str_n;
	if (fd == 1)
		data->type = 'p';
	else if (fd != -1)
		data->type = 'd';
	if (str)
	{
		if (str_n != -1)
			data->type = 'n';
		else if (data->as)
		{
			data->type = 'a';
			*str = NULL;
		}
		else
			data->type = 's';
	}
	return (1);
}

void	conv_ptr(t_printf *data)
{
	data->width -= data->flags & (1 << 1) ? 2 : 0;
	data->pad = (data->printed > data->width - 3)
	? 0 : data->width - 3 - data->printed;
	data->flags |= (1 << 12);
	data->flags |= (1 << 0);
	conv_uint(data);
}

void	conv_esc(t_printf *data)
{
	data->pad = data->width - 1;
	if (data->pad > 0)
	{
		add_pad(data, 0);
		buffer("%", data, 1);
		add_pad(data, 1);
	}
	else
		buffer("%", data, 1);
}

void	init_data(t_printf *data, const char *format, int as)
{
	ft_bzero(data, sizeof(*data));
	data->fmt = (char*)format;
	if (as)
		data->as = 1;
	else
		data->as = 0;
}
