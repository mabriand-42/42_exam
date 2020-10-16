#include "ft_printf.h"

int		ft_put_s(t_flag flag, va_list *ap)
{

	char	*s;
	int		size;
	int		w;
	int		p;
	int		i;

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
	if (flag.f == 1)
		i = w + p;
	else
		i = w + size;
	while (w > 0)
	{
		write(1, " ", 1);
		w--;
	}
	if (flag.f == 1)
		write(1, s, p);
	else
		write(1, s, size);
	return (i);
}

int		ft_put_d(t_flag	flag, va_list *ap)
{
	int	nbr;
	int size;
	int w;
	int p;
	int i;

	nbr = va_arg(*ap, int);
	size = ft_nbrlen_d(nbr);
	p = 0;
	w = 0;
	i = 0;
	if (flag.preci > size)
		p = flag.preci - size;
	if (flag.width > (p + size))
		w = flag.width - (p + size);
	i = w + p + size;
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
		i++;
	}
	while (p > 0)
	{
		write(1, "0", 1);
		p--;
	}
	ft_putnbr_d(nbr);
	return (i);
}

int		ft_put_x(t_flag	flag, va_list *ap)
{
	int	nbr;
	int size;
	int w;
	int p;
	int i;

	nbr = va_arg(*ap, unsigned int);
	size = ft_nbrlen_d(nbr);
	p = 0;
	w = 0;
	if (flag.preci > size)
		p = flag.preci - size;
	if (flag.width > p + size)
		w = flag.width - (p + size);
	i = w + p + size;
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
	return (i);
}