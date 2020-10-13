#ifndef FT_PRINTF_H
#define FT_PRINTF_H


#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

typedef	struct	s_flag
{
	int	width;
	int	preci;
}				t_flag;


int		ft_search(char *str);
int		ft_is_arg(char *str);
int		ft_strlen(char *str);
int		ft_nbrlen_d(int n);
int		ft_nbrlen_x(unsigned int n);
void	ft_putnbr_d(int n);
void	ft_putnbr_x(unsigned int n);
int		ft_put_s(t_flag flag, va_list *ap);
int		ft_put_d(t_flag	flag, va_list *ap);
int		ft_put_x(t_flag	flag, va_list *ap);

t_flag	ft_get_flag(char *str, int *pos);
int		ft_printf(const char *str, ...);

#endif