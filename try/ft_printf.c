/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:02:57 by mabriand          #+#    #+#             */
/*   Updated: 2020/10/19 13:44:56 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		printed;
	t_flag	flag;

	va_start(ap, str);
	i = 0;
	printed = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
		{
			write(1, &str[i], 1);
			printed++;
		}
		else if (ft_isarg((char *)str + i + 1))
		{
			flag = ft_get_flag((char *)str, &i);
			if (str[i] == 's')
				printed += ft_put_s(flag, &ap);
			if (str[i] == 'd')
				printed += ft_put_d(flag, &ap);
			if (str[i] == 'x')
				printed += ft_put_x(flag, &ap);
		}
		i++;
	}
	return (printed);
}

int		ft_isarg(char *str)
{
	int i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
	}
	if (str[i] == 's' || str[i] == 'd' || str[i] == 'x')
		return (1);
	return (0);
}

t_flag		ft_get_flag(char *str, int *pos)
{
	t_flag flag;

	flag.preci = 0;
	flag.width = 0;
	flag.f = 0;
	(*pos)++;
	while (str[*pos] >= '0' && str[*pos] <= '9')
	{
		flag.width *= 10;
		flag.width += str[*pos] - 48;
		(*pos)++;
	}
	if (str[*pos] == '.')
	{
		(*pos)++;
		while (str[*pos] >= '0' && str[*pos] <= '9')
		{
			flag.preci *= 10;
			flag.preci += str[*pos] - 48;
			(*pos)++;
		}
		flag.f = 1;
	}
	return (flag);
}


