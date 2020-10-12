#include "ft_printf.h"

int		ft_printf(const char *str, ...)
{
	va_list	ap;
	t_flag	flag;

	int i;
	int printed;
	int	ret;

	va_start(ap, str);
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
			flag = ft_get_flag(str, &i);
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


	nbr = va_arg(*ap, int);

}


int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
		i++;
	return (i);
}
