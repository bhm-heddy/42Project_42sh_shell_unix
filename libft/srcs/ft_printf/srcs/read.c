#include "ft_printf.h"

void		read_flags(t_printf *data)
{
	while ((data->f_index = ft_strchri("#0- +", *(data->fmt))) > -1)
	{
		data->flags |= (1 << data->f_index);
		(data->fmt)++;
	}
	if (data->flags & (1 << 2))
		data->flags &= ~(1 << 1);
	if (data->flags & (1 << 4))
		data->flags &= ~(1 << 3);
}

void		read_width(t_printf *data)
{
	if (ft_isdigit(*data->fmt))
	{
		data->width = ft_atoi(data->fmt);
		while (ft_isdigit(*(data->fmt)))
			(data->fmt)++;
	}
	else if (*(data->fmt) == '*')
	{
		data->width = va_arg(data->ap, int);
		if (data->width < 0)
		{
			data->width = -data->width;
			data->flags |= (1 << 2);
		}
		(data->fmt)++;
	}
}

void		read_prec(t_printf *data)
{
	if (*(data->fmt) == '.')
	{
		(data->fmt)++;
		if (*(data->fmt) == '*')
		{
			data->prec = va_arg(data->ap, int);
			(data->fmt)++;
		}
		else
		{
			if (ft_isdigit(*(data->fmt)))
				data->prec = ft_atoi(data->fmt);
			while (ft_isdigit(*(data->fmt)))
				(data->fmt)++;
		}
		if (data->prec >= 0)
			data->flags |= (1 << 15);
		data->prec = (data->prec < 0) ? 0 : data->prec;
	}
}

void		read_length_mod(t_printf *data)
{
	if (*(data->fmt) == 'l')
	{
		data->flags |= (*(data->fmt + 1) == 'l') ? (1 << 10) : (1 << 9);
		(data->fmt)++;
	}
	else if (*(data->fmt) == 'h')
	{
		data->flags |= (*(data->fmt + 1) == 'h') ? (1 << 8) : (1 << 7);
		(data->fmt)++;
	}
	else if (*(data->fmt) == 'L')
		data->flags |= (1 << 10);
	else if (*(data->fmt) == 'z')
		data->flags |= (1 << 13);
	else if (*(data->fmt) == 'j')
		data->flags |= (1 << 14);
	if (ft_strchr("lhLzj", *(data->fmt)))
		(data->fmt)++;
	if (ft_strchr("DOUFBCSX", *data->fmt))
		data->flags |= (*data->fmt == 'X') ? (1 << 11) : (1 << 9);
}

void		read_conv_spec(t_printf *data)
{
	int				i;
	static void		(*disp[11])(t_printf *);

	if (!data->disp_set)
		init_dispatcher(data, disp);
	data->conv = *(data->fmt);
	if (ft_strchr("idDoOuUxXbB", *(data->fmt)) && data->flags & (1 << 15))
		data->flags &= ~(1 << 1);
	if (*(data->fmt) == 'i')
		disp[0](data);
	else if ((i = ft_strchri("DOUFBCSX", *(data->fmt))) > -1)
		disp[i](data);
	else if ((i = ft_strchri("doufbcsxp%m{", *(data->fmt))) > -1)
		disp[i](data);
	else
		buffer(data->err_ptr, data, (data->fmt - data->err_ptr));
}
