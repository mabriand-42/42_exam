/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:02:57 by mabriand          #+#    #+#             */
/*   Updated: 2020/10/19 14:01:36 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char	*ft_recursive(int fd, int *ret, int depth)
{
	char	buf[1];
	char	*out;
	int		test;

	test = read(fd, buf, 1);
	if (test == 0)
		buf[0] = '\0';
	if (buf[0] == '\n' || buf[0] == '\0')
	{
		if (!(out = malloc(sizeof(char) * depth + 1)))
			return (0);
		out[depth] = '\0';
		*ret = 1;
		if (buf[0] == '\0')
			*ret = 0;
		//return (out);
	}
	else
	{
		if (!(out = ft_recursive(fd, ret, depth + 1)))
			return (0);
		out[depth] = buf[0];
	}
	return (out);
}

int		get_next_line(int fd, char **out)
{
	int	ret;

	ret = 1;
	*out = ft_recursive(fd, &ret, 0);
	return (ret);
}

int		main(void)
{
	int		r;
	int		fd;
	char	*line;

	/*if ((fd = open("test.txt", O_RDONLY)) == -1)
		return (0);*/
	fd = 0;
	line = NULL;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
}
