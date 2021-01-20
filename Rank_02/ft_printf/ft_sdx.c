#include "ft_printf.h"

int     ft_put_s(t_flag flag, va_list *ap)
{
    char    *str;
    int     size;
    int     p;
    int     w;
    int     printed;

    str = va_arg(*ap, char *);
    size = ft_strlen(str);
    p = 0;
    w = 0;
    printed = 0;
    if (flag.preci < size)
        p = flag.preci;
    else
        p = size;
    
    if (flag.width > p)
        w = flag.width - p;
    else
        w = 0;
    if (flag.f == 0)
        printed = w + size;
    else
        printed = w + p;
    while (w > 0)
    {
        write(1, " ", 1);
        w--;
    }
    if (flag.f == 0)
        write(1, str, size);
    else
        write(1, str, p);
    return (printed);
}

int     ft_put_d(t_flag flag, va_list *ap)
{
    int nbr;
    int size;
    int p;
    int w;
    int printed;

    nbr = va_arg(*ap, int);
    size = ft_nbrlen_d(nbr);
    p = 0;
    w = 0;
    printed = 0;
    if (flag.preci > size)
        p = flag.preci - size;
    if (flag.width > (p + size))
        w = flag.width - (p + size);
    printed = w + p + size;
    if (nbr < 0 && w)
        w -= 1;
    while (w > 0)
    {
       write(1, " ", 1);
		w--; 
    }
    if (nbr < 0)
    {
        write(1, "-", 1);
        printed++;
    }
    while (p > 0)
	{
		write(1, "0", 1);
		p--;
	}
	ft_putnbr_d(nbr);
	return (printed);
}


int     ft_put_x(t_flag flag, va_list *ap)
{
    unsigned int nbr;
    int size;
    int p;
    int w;
    int printed;

    nbr = va_arg(*ap, unsigned int);
    size = ft_nbrlen_x(nbr);
    p = 0;
    w = 0;
    printed = 0;
    if (flag.preci > size)
        p = flag.preci - size;
    if (flag.width > (p + size))
        w = flag.width - (p + size);
    printed = w + p + size;
    while (w > 0)
    {
       write(1, " ", 1);
		w--; 
    }
    while (p > 0)
	{
		write(1, "0", 1);
		p--;
	}
	ft_putnbr_x(nbr);
	return (printed);
}