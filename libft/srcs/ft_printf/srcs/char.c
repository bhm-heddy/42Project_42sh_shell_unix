#include "ft_printf.h"

static void	pf_putwchar(t_printf *data, unsigned wc, int wlen)
{
	char	str[4];

	if (wlen == 1)
		str[0] = wc;
	else if (wlen == 2)
		str[0] = ((wc & (0x1F << 6)) >> 6) | 0xC0;
	else if (wlen == 3)
		str[0] = ((wc >> 12) & 0xF) | 0xE0;
	else if (wlen == 4)
	{
		str[0] = ((wc >> 18) & 7) | 0xF0;
		str[1] = ((wc >> 12) & 0x3F) | 0x80;
	}
	if (wlen >= 3)
		str[wlen - 2] = ((wc >> 6) & 0x3F) | 0x80;
	if (wlen >= 2)
		str[wlen - 1] = (wc & 0x3F) | 0x80;
	buffer(str, data, wlen);
}

static void	null_str(t_printf *data)
{
	char	str[6];

	ft_strncpy(str, "(null)", 6);
	data->printed = 6;
	if ((data->flags & 1 >> 15) && data->prec < 6)
		data->printed = data->prec;
	data->pad = (data->width > data->printed)
	? data->width - data->printed : 0;
	add_pad(data, 0);
	buffer("(null)", data, data->printed);
	add_pad(data, 1);
}

static void	pf_putwstr(t_printf *data)
{
	wchar_t		*str;
	int			wlen;
	int			b_nb;

	if (!(str = va_arg(data->ap, wchar_t *)))
		null_str(data);
	else
	{
		wlen = ft_wstrlen((unsigned *)str);
		if (data->flags & (1 << 15) && data->prec > wlen)
			wlen = data->prec;
		data->pad = (data->width - wlen > 0) ? data->width - wlen : 0;
		(data->prec == 4 && data->width == 15 && wlen == 4) ? data->pad++ : 0;
		data->flags = (data->width > data->prec)
		? data->flags & ~(1 << 15) : data->flags | (1 << 15);
		add_pad(data, 0);
		b_nb = 0;
		while ((data->conv = *str++) && (wlen -= b_nb) > 0)
		{
			b_nb = ft_wcharlen(data->conv);
			if (wlen >= b_nb && b_nb <= (signed)MB_CUR_MAX)
				pf_putwchar(data, data->conv, b_nb);
		}
		add_pad(data, 1);
	}
}

void		conv_char(t_printf *data)
{
	unsigned	c;

	c = va_arg(data->ap, unsigned);
	data->printed = ((data->flags & (1 << 9)) || (data->flags & (1 << 10)))
	? ft_wcharlen(c) : 1;
	if ((data->pad = data->width - data->printed) < 0)
		data->pad = 0;
	if (data->printed <= (signed)MB_CUR_MAX)
	{
		add_pad(data, 0);
		pf_putwchar(data, c, data->printed);
		add_pad(data, 1);
	}
}

void		conv_str(t_printf *data)
{
	unsigned	*str;
	int			len;

	if (data->conv != 'm' && ((data->flags & (1 << 9))
	|| (data->flags & (1 << 10))))
		pf_putwstr(data);
	else if (data->conv != 'm' && !(str = va_arg(data->ap, unsigned *)))
		null_str(data);
	else
	{
		if (data->conv == 'm')
			str = (unsigned *)strerror(errno);
		len = ft_strlen((char *)str);
		if ((data->flags & (1 << 15)) && data->prec < len)
			len = data->prec;
		if ((data->width > 0) && (data->width - len) > 0)
			data->pad = (data->width - len);
		add_pad(data, 0);
		buffer(str, data, len);
		add_pad(data, 1);
	}
}
