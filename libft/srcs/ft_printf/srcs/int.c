#include "ft_printf.h"

static intmax_t		get_int_val(t_printf *data)
{
	intmax_t	val;

	if (data->flags & (1 << 9))
		val = (intmax_t)(va_arg(data->ap, long));
	else if (data->flags & (1 << 10))
		val = (intmax_t)va_arg(data->ap, long long);
	else if (data->flags & (1 << 13))
		val = (intmax_t)va_arg(data->ap, ssize_t);
	else if (data->flags & (1 << 14))
		val = va_arg(data->ap, intmax_t);
	else if (data->flags & (1 << 7))
		val = (intmax_t)((short int)va_arg(data->ap, int));
	else if (data->flags & (1 << 8))
		val = (intmax_t)((char)va_arg(data->ap, int));
	else
		val = (intmax_t)va_arg(data->ap, int);
	if (data->flags & (1 << 1))
		data->prec = data->width;
	return (val);
}

static void			add_prefix(t_printf *data, intmax_t tmp,
		uintmax_t val, char *s)
{
	add_pad(data, 0);
	val = (tmp < 0) ? -tmp : tmp;
	xtoa_base(val, 10, s, data);
	data->flags & (1 << 3) ? s[0] = ' ' : 0;
	(tmp < 0) ? s[0] = '-' : 0;
	(data->flags & (1 << 4) && tmp >= 0) ? s[0] = '+' : 0;
}

void				conv_int(t_printf *data)
{
	char		s[200];
	uintmax_t	val;
	intmax_t	tmp;
	int			len;

	tmp = get_int_val(data);
	val = (tmp < 0) ? -tmp : tmp;
	len = (!tmp && !(data->flags & (1 << 15))) ? 1 : 0;
	while (val)
	{
		val /= 10;
		len++;
	}
	if ((tmp < 0 || data->flags & (1 << 4) || data->flags & (1 << 3))
	&& data->flags & (1 << 1))
		(data->prec)--;
	data->printed = (len > data->prec) ? len : data->prec;
	(tmp < 0 || data->flags & (1 << 4) || data->flags & (1 << 3))
	? (data->printed)++ : 0;
	data->pad = (data->printed > data->width) ? 0 : data->width - data->printed;
	add_prefix(data, tmp, val, s);
	buffer(s, data, data->printed);
	add_pad(data, 1);
}
