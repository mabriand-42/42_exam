/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 11:07:26 by mabriand          #+#    #+#             */
/*   Updated: 2020/10/19 13:44:09 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_nbrlen_d(int nbr)
{
	int i;
	
	i = 0;
	if (!nbr)
		return (1);
	if (nbr == -2147483648)
		return (10);
	while (nbr > 10)
	{
		nbr /= 10;
		i++;
	}
	i++;
	return (i);
}

int		ft_nbrlen_x(unsigned int nbr)
{
	int i;

	i = 0;
	if (!nbr)
		return (1);
	while (nbr > 16)
	{
		nbr /= 16;
		i++;
	}
	i++;
	return (i);
}

void	ft_putnbr_d(int nbr)
{
	int		x;
	char	c;
	char	*base;

	x = 1;
	base = "0123456789";
	if (nbr == -2147483648)
	{	
		write(1, "2147483648", 10);
		return ;
	}
	if (nbr < 0)
		nbr *= -1;
	while ((nbr / x) >= 10)
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
	unsigned int	x;
	char			c;
	char			*base;

	x = 1;
	base = "0123456789abcdef";
	while ((nbr / x) >= 16)
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

