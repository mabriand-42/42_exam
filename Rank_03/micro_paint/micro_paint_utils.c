#include "micro_paint.h"

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str[i] != '\0')
        i++;
    return(i);
}

int ft_putstr(char *str)
{
    write(1, str, ft_strlen(str));
    return (1);
}

