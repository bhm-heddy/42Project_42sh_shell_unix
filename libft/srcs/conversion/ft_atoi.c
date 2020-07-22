int		ft_atoi(const char *str)
{
	int i;
	int s;
	int r;

	i = 0;
	s = 1;
	r = 0;
	while (str && str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == ' '))
		++i;
	if (str && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			s *= -1;
		i += 1;
	}
	while (str && str[i] && str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + (str[i] - 48);
		i++;
	}
	return (r * s);
}
