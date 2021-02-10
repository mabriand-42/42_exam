#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct	s_flag
{
	int preci;
	int width;
	int f;
}		t_flag;


int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_nbrlen_x(unsigned int nbr)
{
	int i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

int	ft_nbrlen_d(int nbr)
{
	int i;

	i = 0;
	if (!nbr)
		return (1);
	if (nbr == -2147483648)
		return (10);
	if (nbr < 0)
		nbr *= -1;
	while (nbr > 0)
	{
		nbr /= 10;
		i++;	
	}
	return (i);
}

void	ft_putnbr_d(int nbr)
{
	int div;
	int len;
	char c;
	char *base;

	div = 1;
	len = ft_nbrlen_d(nbr);
	c = '0';
	base = "0123456789";
	if (!nbr)
		write(1, "0", 1);
	else if (nbr == -2147483648)
		write(1, "2147483648", 10);
	else
	{	
		if (nbr < 0)
			nbr *= -1;	
		while (len > 1)
		{
			div *= 10;
			len--;
		}
		while (nbr > 0)
		{	
			c = base[nbr/div];
			write(1, &c, 1);
			nbr %= div;
			div /= 10;
		}
	}
	return ;
}



void	ft_putnbr_x(unsigned int nbr)
{
	int	div;
	int	len;
	char	c;
	char 	*base;

	div = 1;
	len = ft_nbrlen_x(nbr);
	base = "0123456789abcdef";
	if (!nbr)
		write(1, "0", 1);
	else
	{
		while (len > 1)
		{
			div *= 16;
			len--;
		}
		while (nbr > 0)
		{
			c = base[nbr/div];
			write(1, &c, 1);
			nbr %= div;
			div /= 16;
		}
	}
	return ;
}

int	ft_put_s(t_flag flag, va_list *ap)
{
	char 	*str;
	int	size;
	int	p;
	int 	w;
	int	printed;

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


int     ft_isflag(char *str)
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

t_flag	ft_getflag(char *str, int *i)
{
	t_flag flag;

	flag.f = 0;
	flag.width = 0;
	flag.preci = 0;
	 *i += 1;
	while(str[*i] >= '0' && str[*i] <= '9')
	{	
		flag.width *= 10;
		flag.width += str[*i] - 48;
		(*i)++;
	}	
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			flag.preci *= 10;
			flag.preci += str[*i] - 48;
			(*i)++;
		}
		flag.f = 1;
	}
	return (flag);
}

int	ft_printf(const char *str, ...)
{	
	va_list ap;
	t_flag	flag;
	int 	i;
	int	printed;

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
		else if (ft_isflag((char *)str + i + 1) == 1)
		{
			flag = ft_getflag((char *)str, &i);
			if (str[i] == 's')
				printed += ft_put_s(flag, &ap);	
			if (str[i] == 'd')
				printed += ft_put_d(flag, &ap);	
			if (str[i] == 'x')
				printed += ft_put_x(flag, &ap);	
		}
		i++;
	}
	va_end(ap);
	return (printed);
}

int	main()
{
	int ret = 0;
	ret = ft_printf("salutsalut %4.5s = %d\n %x", "   mariebriand", 0, -98);
	printf("ret = %d\n", ret);
	ret = printf("salutsalut %4.5s = %d\n %x", "   mariebriand", 0, -98);
	printf("printf ret = %d\n", ret);
	printf("------------------------------\n");
	ret = ft_printf("");
	printf("ret = %d\n", ret);
	ret = printf("");
	printf("printf ret = %d\n", ret);
}
