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


void	ft_puttab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		write(1, "\n", 1);
		i++;
	}
}

int		ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}
