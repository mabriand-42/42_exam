#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

int     ft_isalready(char c, char *str, int pos)
{
    int i;

    i = 0;
    while (i < pos)
    {
        if (c == str[i])
            return (1);
        i++;
    }
    return (0);
}

void    ft_union(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] != '\0')
    {
        if (ft_isalready(s1[i], s1, i) == 0)
            write (1, &s1[i], 1);
        i++;
    }
    i = 0;
    while (s2[i] != '\0')
    {
        if(ft_isalready(s2[i], s1, ft_strlen(s1)) == 0 && ft_isalready(s2[i], s2, i) == 0)
            write (1, &s2[i], 1);
        i++;
    }
    return ;
}

int     main(int argc, char **argv)
{
    
    if (argc != 3)
    {
        write(1, "\n", 1);
        return (0);
    }
    else
        ft_union(argv[1], argv[2]);
        write(1, "\n", 1);
    return (0);
}