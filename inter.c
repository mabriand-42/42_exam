/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:04:28 by mabriand          #+#    #+#             */
/*   Updated: 2020/09/17 17:00:28 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_already(char c, char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_inter(char *s1, char *s2)
{
	int		max;
	char	*str;
	int		j;
	int		k;
	int		l;


	int a = ft_strlen(s1);
	int b = ft_strlen(s2);
	printf("chaine 1 = %d || chaine 2 = %d\n", a, b);

	/*if (ft_strlen(s1) < ft_strlen(s2))*/
	if (a > b)
		max = a;
		//max = ft_strlen(s1);
	else
		max = b;
		//max = ft_strlen(s2);
	printf("MAX = %d\n", max);
	str = (char *)malloc(sizeof(char) * max + 1);
	//*str='p';
	if (!str)
		return (NULL);
	j = 0;
	l = 0;
	while (s1[j] != '\0')
	{

		k = 0;
		while (s2[k] != '\0')
		{
			//printf("\ns1[%d] = %c || s2[%d] = %c", j, s1[j], k, s2[k]);
			if (s1[j] == s2[k] && (ft_already(s1[j], str) == 0))
			{
				//printf("\n==========> str[%d] = %c || s1[%d] = %c", l, str[l], j, s1[j]);
				str[l] = s1[j];
			//	printf("\n//////////> str[%d] = %c || s1[%d] = %c", l, str[l], j, s1[j]);
				//printf("\nstr[%d] = %c || s1[%d] = %c", l, str[l], j, s1[j]);
				l++;
				break ;
			}
			else
				k++;
		}
		j++;
	}
	str[l] = '\0';
	return (str);
}

int		main(int argc, char **argv)
{
	char	*i;

	i = NULL;
	if (argc != 3)
	{
		write (1, "\n", 1);
		return (0);
	}
	i = ft_inter(argv[1], argv[2]);
	write(1, i, ft_strlen(i));
	write(1, "\n", 1);
	return (0);
}
