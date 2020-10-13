#include "ft_printf.h"

int		ft_printf(const char *str, ...)
{
	va_list	ap;
	t_flag	flag;

	int i;
	int printed;
	int	ret;

	i = 0;
	va_start(ap, str);
	printed = 0;
	ret = ft_search((char *)str);
	while (str[i])
	{
		if (str[i]!= '%')
		{
			write(1, &str[i], 1);
			printed++;
		}
		else if (ft_is_arg((char *)str + i + 1))
		{
			flag = ft_get_flag((char *)str, &i);
			if(str[i] == 's')
				ret += ft_put_s(flag, &ap);
			if(str[i] == 'd')
				ret += ft_put_s(flag, &ap);
			if(str[i] == 'x')
				ret += ft_put_s(flag, &ap);
		}
		i++;
	}
	va_end(ap);
	return (printed);
}

int		ft_search(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (ft_is_arg(str + i + 1) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int		ft_is_arg(char *str)
{
	int i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i++] == '.')
	{
		while (str[i] >= '0' && str[i] <= '9')
			i++;
	}
	if (str[i] == 's' || str[i] == 'd' || str[i] == 'x')
		return (1);
	return (0);
}

t_flag	ft_get_flag(char *str, int *pos)
{
	t_flag	flag;

	flag.width = 0;
	flag.preci = 0;
	*pos += 1;
	while (str[*pos] >= '0' && str[*pos] <= '9')
	{
		flag.width *= 10;
		flag.width += str[*pos] - 48;
		(*pos)++;
	}
	if (str[*pos] == '.')
	{
		(*pos)++;
		while (str[*pos] >= '0' && str[*pos] <= '9')
		{
		flag.preci *= 10;
		flag.preci += str[*pos] - 48;
		(*pos)++;
		}
	}
	return (flag);
}

int		ft_put_s(t_flag flag, va_list *ap)
{

	char	*s;
	int		size;
	int		w;
	int		p;


	s = va_arg(*ap, char *);
	size = ft_strlen(s);

	if (flag.preci < size)
		p = flag.preci;
	else
		p = size;
	if (flag.width > p)
		w = flag.width - p;
	else
		w = 0;

	while (w > 0)
	{
		write(1, " ", 1);
		w--;
	}
	write(1, s, p);
	return (w + p);
}

int		ft_put_d(t_flag	flag, va_list *ap)
{
	int	nbr;
	int size;
	int w;
	int p;

	nbr = va_arg(*ap, int);
	size = ft_nbrlen_d(nbr);

	p = 0;
	w = 0;
	if (flag.preci > size)
		p = flag.preci - size;
	if (flag.width > p + size)
		w = flag.width = p + size;
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
		w++;
	}
	while (p > 0)
	{
		write(1, "0", 1);
		p--;
	}
	ft_putnbr_d(nbr);
	return (w + p + size);
}

int		ft_put_x(t_flag	flag, va_list *ap)
{
	int	nbr;
	int size;
	int w;
	int p;

	nbr = va_arg(*ap, unsigned int);
	size = ft_nbrlen_d(nbr);

	p = 0;
	w = 0;
	if (flag.preci > size)
		p = flag.preci - size;
	if (flag.width > p + size)
		w = flag.width = p + size;
	if (nbr < 0 && w)
		w -= 1;
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
	return (w + p + size);
}

void	ft_putnbr_d(int n)
{
	int		x;
	char	c;

	x = 1;
	c = 48;
	if (n == -2147483648)
	{
		write(1, "2147483648", 10);
		return ;
	}
	if (n < 0)
		n *= -1;
	while (n / x >= 10)
		x *= 10;
	while (x)
	{
		c = (n / x + 48);
		write(1, &c, 10);
		n %= x;
		x /= 10;
	}
	return ;
}

void	ft_putnbr_x(unsigned int n)
{
	unsigned int	x;
	char			c;
	char 			*base;

	x = 1;
	c = 48;
	base = "0123456789abcdef";
	while (n / x >= 16)
		x *= 16;
	while (x)
	{
		c = base[n/x];
		write(1, &c, 10);
		n %= x;
		x /= 16;
	}
	return ;
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
		i++;
	return (i);
}

int		ft_nbrlen_d(int n)
{
	int i;

	i = 0;
	if (!n)
		return (0);
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

int		ft_nbrlen_x(unsigned int n)
{
	int i;

	i = 0;
	if (!n)
		return (0);
	if (n < 0)
		n *= -1;
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

int	main()
{
	int ret = 0;
	ret = ft_printf("salutsalut%23.4d%30.7s    %x|\n", -2147483648, "i42424242424224242424242424242424242", -42);
	printf("ret = %d\n", ret);
	ret = ft_printf("salutsalut%23.4d%30.7s    %x|\n", -2147483648, "i42424242424224242424242424242424242", -42);
	printf("ret = %d\n", ret);
	ret = ft_printf("");
	printf("ret = %d\n", ret);
	ret = ft_printf("");
	printf("ret = %d\n", ret);
}