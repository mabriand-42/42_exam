#include "get_next_line.h"

static int	ft_recursive(char **line, size_t index, int fd)
{
	int	ret;
	char	buf;

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

int		get_next_line(char **line)
{
	int ret;
	ret = ft_recursive(line, 0, 0);
	return (ret);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		main(void)
{
	int	ret;
	char 	*line;

	while ((ret = get_next_line(&line)) > 0)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		free(line);
		line = NULL;
	}
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
	free(line);
	line = NULL;
	return (0);
}


