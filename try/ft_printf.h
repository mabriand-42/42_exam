/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:18:29 by mabriand          #+#    #+#             */
/*   Updated: 2020/10/19 12:27:28 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H_
#define _FT_PRINTF_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

typedef	struct	s_flag
{
	int		width;
	int		preci;
	int		f;
}				t_flag;

int		ft_printf(const char *str, ...);
int		ft_isarg(char *str);
t_flag	ft_get_flag(char *str, int *pos);
int		ft_put_x(t_flag flag, va_list *ap);
int		ft_put_d(t_flag flag, va_list *ap);
int		ft_put_s(t_flag	flag, va_list *ap);
void	ft_putnbr_x(unsigned int nbr);
void	ft_putnbr_d(int	nbr);
int		ft_nbrlen_x(unsigned int nbr);
int		ft_nbrlen_d(int nbr);
int		ft_strlen(char *str);

#endif
