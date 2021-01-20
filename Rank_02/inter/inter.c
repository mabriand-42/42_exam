#include <unistd.h>
#include <stdio.h>

int     ft_isalready(char c, char *str, int pos)
{
    int i;

    i = 0;
    while (i < pos)
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}


void    ft_inter(char *s1, char *s2)
{
    int i;
    int j;

    i = 0;
    while (s1[i] != '\0')
    {
        j = 0;
        while (s2[j] != '\0')
        {
            if (s1[i] == s2[j] && ft_isalready(s1[i], s1, i) == 0)
            {
                write(1, &s1[i], 1);
                //j = 0;
                break;
            }
            else
                j++;
        }
        i++;
    }
    write(1, "\n", 1);
    return ;
}


int     main (int argc, char **argv)
{
    if (argc != 3)
        write(1, "\n", 1);
    else
        ft_inter(argv[1], argv[2]);
    return (0);
}