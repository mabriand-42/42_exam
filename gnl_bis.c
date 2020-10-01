/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:47:45 by mabriand          #+#    #+#             */
/*   Updated: 2020/10/01 15:24:54 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static int		ft_recursive(char  **line, size_t index, int fd)
{
	char	buf;
	int		ret;

	ret = read(fd, &buf, 1);
	if (ret == 1 && buf != '\n')
	{
		ft_recursive(line, index + 1, fd);
		(*line)[index] = buf;
	}
	else
	{
		*line = (char *)malloc(sizeof(char) * index + 1);
		(*line)[index] = '\0';
	}
	return (ret);
}

int		gnl(char **line)
{
	int		ret;

	ret = ft_recursive(line, 0, 0);
	return (ret);
}

int		main(void)
{
	int		r;
	char	*line;

	line = NULL;
	while ((r = gnl(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
}
