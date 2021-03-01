#ifndef _MICRO_PAINT_H_
# define _MICRO_PAINT_H_

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef struct  s_zone
{
    int     w;
    int     h;
    char    back;
}               t_zone;

typedef struct  s_rect
{
    char    type;
    float   x;
    float   y;
    float   w;
    float   y;
    char    c;
}               t_rect;

int     ft_strlen(char *str);
int     ft_putstr(char *str);
void    ft_puttab(char **tab);
int     ft_freetab(char **tab); 

#endif