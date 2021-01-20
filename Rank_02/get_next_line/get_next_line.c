#include "get_next_line.h"

static int  ft_recursive(char **line, size_t index, int fd)
{
    int     ret;
    char    buf;

    ret = read(fd, &buf, 1);
    if (ret == 1 && buf != '\n')
    {
        ft_recursive(line, index + 1, fd);
        (*line)[index] = buf;
    }
    else
    {
        (*line) = (char *)malloc(sizeof(char) * index + 1);
        (*line)[index] = '\0';
    }
    return (ret);
}

int         get_next_line(char **line)
{
    int ret;

    ret = ft_recursive(line, 0, 0);
    return (ret);
}
