#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct  s_flag
{
    int width;
    int preci;
    int f;
}               t_flag;

/*
** Printf
*/
int     ft_printf(const char *str, ...);
int     ft_isflag(char *str);
t_flag  ft_getflag(char *str, int *pos);

/*
** Utils
*/
int     ft_strlen(char *str);
int     ft_nbrlen_d(int n);
int     ft_nbrlen_x(unsigned int n);

void    ft_putnbr_d(int n);
void    ft_putnbr_x(unsigned int n);

int     ft_put_s(t_flag flag, va_list *ap);
int     ft_put_d(t_flag flag, va_list *ap);
int     ft_put_x(t_flag flag, va_list *ap);

#endif