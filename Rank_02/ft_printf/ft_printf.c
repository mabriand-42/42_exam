#include "ft_printf.h"

int     ft_printf(const char *str, ...)
{
    va_list ap;
    t_flag  flag;
    int     i;
    int     printed;

    va_start(ap, str);
    i = 0;
    printed = 0;
    while(str[i])
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

t_flag  ft_getflag(char *str, int *pos)
{
    t_flag  flag;
    
    flag.f = 0;
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
        flag.f = 1; 
    }
    return (flag);
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