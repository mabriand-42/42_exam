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

t_flag	ft_get_flag(char *str, int *pos);

#endif