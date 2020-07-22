int		ft_recursive_power(int nb, int pw)
{
	if (pw < 0)
		return (0);
	else if (pw == 0)
		return (1);
	else
		return (ft_recursive_power(nb, pw - 1) * nb);
}
