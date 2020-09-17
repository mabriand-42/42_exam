/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:03:21 by mabriand          #+#    #+#             */
/*   Updated: 2020/09/14 15:03:32 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_already(char c, char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

char	*ft_union(char *s1, char *s2)
{
	int		max;
	int		i;
	int		k;
	char	*u;

	max = ft_strlen(s1) + ft_strlen(s2);
	u = (char *)malloc(sizeof(char) * max + 1);
	if (!u)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
		u[k++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
	{
		if (ft_already(s2[i], u) == 1)
			i++;
		else
			u[k++] = s2[i++];
	}
	return (u);
}

int		main(int argc, char **argv)
{
	char	*u;

	u = NULL;
	if (argc != 3)
		return (0);
	u = ft_union(argv[1], argv[2]);
	write(1, u, ft_strlen(u));
}
