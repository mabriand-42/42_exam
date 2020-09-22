#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *str)
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


void    ft_inter(char *s1, char *s2)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (s1[i] != '\0')
    {
        j = 0;
        while (s2[j] != '\0')
        {
            if (s1[i] == s2[j] && ft_isalready(s1[i], s1, i) == 0)
            {
                write(1, &s1[i], 1);
                k++;
                j = 0;
                break;
            }
            else
                j++;
        }
        i++;
    }
    return ;
}

int main (int argc, char **argv)
{
    if (argc != 3)
    {
        write(1, "\n", 1);
        return (0);
    }
    else
    {
        ft_inter(argv[1], argv[2]);
        write(1, "\n", 1);
    }
    return (0);
}