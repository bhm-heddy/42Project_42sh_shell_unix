#include "libft.h"

static char	*write_dig(char *p1, char *buf, int *decpt)
{
	char	*p;

	p = p1;
	*p1 += 5;
	while (*p1 > '9')
	{
		*p1 = '0';
		if (p1 > buf)
			++*--p1;
		else
		{
			*p1 = '1';
			(*decpt)++;
			if (p > buf)
				*p = '0';
			p++;
		}
	}
	*p = 0;
	return (buf);
}

static void	write_fract(char **p1, char **p, char **buf, double *val)
{
	double fj;

	while (*p <= *p1 && *p < &(buf[0][CVTBUFSZ]))
	{
		*val *= 10;
		*val = ft_modf(*val, &fj);
		*(p[0]) = (int)(fj + '0');
		p[0]++;
	}
}

static int	get_fract(char **p, char **p1, char **buf, double *fi)
{
	int		r2;
	double	fj;

	r2 = 0;
	*p1 = &(buf[0][CVTBUFSZ]);
	while (*fi != 0)
	{
		fj = ft_modf(*fi / 10, fi);
		p1[0]--;
		**p1 = (int)((fj + .03) * 10) + '0';
		r2++;
	}
	while (*p1 < &(buf[0][CVTBUFSZ]))
	{
		p[0][0] = p1[0][0];
		p[0]++;
		p1[0]++;
	}
	return (r2);
}

static int	get_dig_n_fract(double *val, char **p, char **p1, char **buf)
{
	double	fi;
	double	fj;
	int		r2;

	r2 = 0;
	*val = ft_modf(*val, &fi);
	if (fi != 0)
	{
		r2 = get_fract(p, p1, buf, &fi);
	}
	else if (*val > 0)
		while ((fj = *val * 10) < 1)
		{
			*val = fj;
			r2--;
		}
	return (r2);
}

char		*ft_fcvt(double val, int ndigits, int *decpt, char *buf)
{
	int		r2;
	char	*p;
	char	*p1;

	p = &buf[0];
	p1 = &buf[CVTBUFSZ];
	r2 = get_dig_n_fract(&val, &p, &p1, &buf);
	p1 = &buf[ndigits];
	p1 += r2;
	*decpt = r2;
	if (p1 < &buf[0])
	{
		buf[0] = 0;
		return (buf);
	}
	write_fract(&p1, &p, &buf, &val);
	if (p1 >= &buf[CVTBUFSZ])
	{
		buf[CVTBUFSZ - 1] = 0;
		return (buf);
	}
	return (write_dig(p1, buf, decpt));
}
