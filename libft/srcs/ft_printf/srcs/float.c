#include "ft_printf.h"

static double	get_float_val(t_printf *data)
{
	double		val;

	if (data->flags & (1 << 10))
		val = (double)va_arg(data->ap, long double);
	else
		val = (double)va_arg(data->ap, double);
	return (val);
}

void			conv_float(t_printf *data)
{
	char		res[CVTBUFSZ];
	char		s[CVTBUFSZ];
	double		val;
	int			i;

	val = get_float_val(data);
	ft_ftoa(val, (data->flags & (1 << 15) ? data->prec : -1), res);
	i = 0;
	ft_bzero((void *)s, CVTBUFSZ);
	data->flags & (1 << 3) ? s[0] = ' ' : 0;
	(data->flags & (1 << 4) && val >= 0) ? s[0] = '+' : 0;
	(s[0]) ? i = 1 : 0;
	data->pad = data->width - ft_strlen(res) + i;
	add_pad(data, 0);
	ft_strcat(s, res);
	buffer(s, data, ft_strlen(s));
	add_pad(data, 1);
}
