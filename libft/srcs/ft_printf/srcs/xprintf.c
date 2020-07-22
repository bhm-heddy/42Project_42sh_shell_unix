#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_printf	data;

	init_data(&data, format, 0);
	va_start(data.ap, format);
	if (!init_type(&data, 1, NULL, -1))
		return (-1);
	while (*(data.fmt))
	{
		if (*(data.fmt) == '%' || *(data.fmt) == '{')
		{
			if (!*(data.fmt + 1))
				break ;
			read_arg(&data);
		}
		else
			buffer(data.fmt, &data, 1);
		data.fmt++;
	}
	flush(&data);
	va_end(data.ap);
	return (data.ret);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	t_printf	data;

	init_data(&data, format, 0);
	va_start(data.ap, format);
	if (!init_type(&data, fd, NULL, -1))
		return (-1);
	while (*(data.fmt))
	{
		if (*(data.fmt) == '%' || *(data.fmt) == '{')
		{
			if (!*(data.fmt + 1))
				break ;
			read_arg(&data);
		}
		else
			buffer(data.fmt, &data, 1);
		data.fmt++;
	}
	flush(&data);
	va_end(data.ap);
	return (data.ret);
}

int		ft_sprintf(char *str, const char *format, ...)
{
	t_printf	data;

	init_data(&data, format, 0);
	va_start(data.ap, format);
	if (!init_type(&data, -1, &str, -1))
		return (-1);
	while (*(data.fmt))
	{
		if (*(data.fmt) == '%' || *(data.fmt) == '{')
		{
			if (!*(data.fmt + 1))
				break ;
			read_arg(&data);
		}
		else
			buffer(data.fmt, &data, 1);
		data.fmt++;
	}
	flush(&data);
	va_end(data.ap);
	return (data.ret);
}

int		ft_snprintf(char *str, size_t size, const char *format, ...)
{
	t_printf	data;

	init_data(&data, format, 0);
	va_start(data.ap, format);
	if (!init_type(&data, -1, &str, (int)size))
		return (-1);
	while (*(data.fmt))
	{
		if (*(data.fmt) == '%' || *(data.fmt) == '{')
		{
			if (!*(data.fmt + 1))
				break ;
			read_arg(&data);
		}
		else
			buffer(data.fmt, &data, 1);
		data.fmt++;
	}
	flush(&data);
	va_end(data.ap);
	return (data.ret);
}

int		ft_asprintf(char **ret, const char *format, ...)
{
	t_printf	data;

	init_data(&data, format, 1);
	va_start(data.ap, format);
	if (!init_type(&data, -1, ret, -1))
		return (-1);
	while (*(data.fmt))
	{
		if (*(data.fmt) == '%' || *(data.fmt) == '{')
		{
			if (!*(data.fmt + 1))
				break ;
			read_arg(&data);
		}
		else
			buffer(data.fmt, &data, 1);
		data.fmt++;
	}
	flush(&data);
	va_end(data.ap);
	return (data.ret);
}
