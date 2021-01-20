#include "ft_printf.h"

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

int     ft_nbrlen_x(unsigned int n)
{
    int i;

    i = 0;
    if (!n)
        return (1);
    while (n != 0)
    {
        n /= 16;
        i++;
    }
    return (i);
}

int     ft_nbrlen_d(int n)
{
    int i;

    i = 0;
    if (!n)
        return (1);
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

void    ft_putnbr_d(int n)
{
    int     len;
    int     div;
    char    c;
    char    *base;

    len = ft_nbrlen_d(n);
    div = 1;
    c = 48;
    base = "0123456789";

    if (!n)
		write(1, "0", 1);
    else if (n == -2147483648)
        write(1, "2147483648", 10);
    else
    {
        if (n < 0)
            n *= -1;
        while (len > 1)
        {   
            div *= 10;
            len--;
        }
        while (div > 0)
        {
            c = base[n/div];
            write(1, &c, 1);
            n %= div;
            div /= 10;
        }
    }
    return ;
}

void    ft_putnbr_x(unsigned int n)
{
    int             len;
    unsigned int    div;
    char            c;
    char            *base;

    len = ft_nbrlen_x(n);
    div = 1;
    c = 48;
    base = "0123456789abcdef";

    if (!n)
		write(1, "0", 1);
    else
    {
        while (len > 1)
        {   
            div *= 16;
            len--;
        }
        while (div > 0)
        {
            c = base[n/div];
            write(1, &c, 1);
            n %= div;
            div /= 16;
        }
    }
    return ;
}
