#include "get_next_line.h"

static int  ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}


int         main(void)
{
    char *line;
    int  ret;

    line = NULL;
    while ((ret = get_next_line(&line)) > 0)
    {
        write(1, line, ft_strlen(line));
        write(1, "\n", 1);
        free(line);
        line = NULL;
    }
    write(1, line, ft_strlen(line));
    free(line);
    line = NULL;
    return (0);
}