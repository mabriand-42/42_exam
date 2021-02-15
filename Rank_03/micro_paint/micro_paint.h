#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

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
    float   h;
    char    c;
}               t_rect;

int     ft_strlen(char *str);
int     ft_putstr(char *str);
void    ft_puttab(char **tab);
int     ft_freetab(char **tab);
int     get_zone(FILE *stream, t_zone *zone, char ***draw);
int     draw_zone(t_zone zone, char **draw);
int     get_rect(FILE *stream, t_zone *zone, char **draw, t_rect *rect);
void     draw_rect(t_zone *zone, char **draw, t_rect *rect);


#endif