/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:31:51 by mabriand          #+#    #+#             */
/*   Updated: 2020/10/14 16:46:29 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strlen(char *str)
{
	int i;
	i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_nbrlen_d(int n)
{
	int i;

	i = 0;
	if (!n)
		return (0);
	if (n == -2147483648)
		return (10);	
	if (n < 0)
		n *= -1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		ft_nbrlen_x(unsigned int n)
{
	int i;

	if (!n)
		return (0);
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

void	ft_putnbr_d(int n)
{
	int		x;
	char	c;

	x = 1;
	c = 48;
	if (n == -2147483648)
	{	
		write(1, "2147483648", 10);
		return ;
	}
	if (n < 0)
		n *= -1;
	while ((n / x) >= 10)
		x*= 10;
	while (x)
	{
		c = (n / x + 48);
		write(1, &c,1);
		n %= x;
		x /= 10;
	}
	return ;
}

void	ft_putnbr_x(unsigned int n)
{
	unsigned int	x;
	char			c;
	char			*base;

	x = 1;
	c = 48;
	base = "0123456789abcdef";
	while((n / x) >= 16)
		x *= 16;
	while(x)
	{
		c = base[n/x];
		write(1, &c, 10);
		n %= x;
		x /= 16;
	}
	return ;
}
