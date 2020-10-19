/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gml.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:52:45 by mabriand          #+#    #+#             */
/*   Updated: 2020/10/19 14:03:37 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int		ft_recursive(int fd, int index, char **line)
{
	int		ret;
	char	buf;

	ret = read(fd, &buf, 1);
	if (ret != 0 && buf != '\n')
	{
		ft_recursive(fd, index + 1, line);
		(*line)[index] = buf;
	}
	else
	{
		*line = (char *)malloc(sizeof(char) * index + 1);
		(*line)[index] = '\0';
	}
	return (ret);
}

int		ft_gnl(char **line)
{
	int		ret;

	ret = ft_recursive(0, 0, line);
	return (ret);
}

int		main(void)
{
	int		r;
	char	*line;

	line = NULL;
	while ((r = ft_gnl(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
	return (0);
}
