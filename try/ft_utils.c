#include "ft_printf.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

int	ft_nbrlen_d(int nbr)
{
	int i;

	i = 0;
	if (!n)
		return (1);
	if (n == -2147483648)
		return (10);
	if (n < 0)
		n *= -1;
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int	ft_nbrlen_x(unsigned int nbr)
{
	int i;

	i = 0;
	if (!n)
		return (1);
	while (nbr > 0)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

void	ft_putnbr_d(int nbr)
{
	int		x;
	char 	c;
	char	*base;

	x = 1;
	c = '0';
	base = "0123456789";
	if (nbr == -2147483648)
	{
		write(1, "2147483648", 10);
		return ;
	}
	if (nbr < 0)
		nbr *= -1;
	while (nbr / x >= 10)
		x *= 10;
	while (x > 0)
	{
		c = base[nbr/x];
		write(1, &c, 1);
		nbr %= x;
		x /= 10;
	}
	return ;
}

void	ft_putnbr_x(unsigned int nbr)
{
	int		x;
	char	c;
	char	*base;

	x = 1;
	c = '0';
	base = "0123456789abcdef";
	while (nbr / x >= 16)
		x *= 16;
	while (x > 0)
	{
		c = base[nbr/x];
		write(1, &c, 1);
		nbr %= x;
		x /= 16;
	}
	return ;
}