#include "ft_printf.h"

int	ft_put_s(t_flag flag, va_list *ap)
{
	char	*s;
	int		size;
	int		len;
	int 	w;
	int		p;

	s = va_arg(*ap, char *);
	size = ft_strlen(s);
	len = 0;
	if (flag.preci >= size)
		p = size;
	else
		p = flag.preci;
	if (flag.width <= p)
		w = 0;
	else
		w = flag.width - p;
	if (flag.f == 1)
	 	len = p + w;
	else
		len = size + w;
	while (w > 0)
	{
		write(1, " ", 1);
		w--;
	}
	if (flag.f == 1)
		write(1, s, p);
	else
		write(1, s, size);
	return (len);
}

int	ft_put_d(t_flag flag, va_list *ap)
{
	int	nbr;
	int size;
	int len;
	int w;
	int p;

	nbr = va_arg(*ap, int);
	size = ft_nbrlen_d(nbr);
	w = 0;
	p = 0;
	len = 0;
	if (flag.preci > size)
		p = flag.preci - size;
	if (flag.width > (p + size))
		w = flag.width - (p + size);
	len = w + p + size;
	if (nbr < 0)
		w--;
	while (w > 0)
	{
		write(1, " ", 1);
		w--;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		len ++;
	}
	while (p > 0)
	{
		write(1, "0", 1);
		p--;
	}
	ft_putnbr_d(nbr);
	return (len);
}

int	ft_put_x(t_flag flag, va_list *ap)
{
	unsigned int	nbr;
	int				size;
	int 			len;
	int 			w;
	int 			p;

	nbr = va_arg(*ap, unsigned int);
	size = ft_nbrlen_x(nbr);
	w = 0;
	p = 0;
	len = 0;
	if (flag.preci > size)
		p = flag.preci - size;
	if (flag.width > (p + size))
		w = flag.width - (p + size);
	len = w + p + size;
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
	printf("len is = %d\n",len);
	ft_putnbr_x(nbr);
	return (len);
}