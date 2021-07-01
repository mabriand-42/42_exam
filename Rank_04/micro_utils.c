/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:30:55 by mabriand          #+#    #+#             */
/*   Updated: 2021/07/01 19:05:11 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

void		ft_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return ;
}

void		ft_fatal()
{
	ft_error("error: fatal\n");
	exit(1);
}

int			ft_cmdSize(char **p_arg, char *str) //Il s'agit d'arguments d'où la '*' supplémentaire car av = tab[ac] de pointeurs
{												//=>	cd folder = "cd" "folder"
	int	i;										//=>	echo something ; echo something else = "echo" "something" ";" "echo" "something" "else"

	i = 0;
	if (!p_arg)
		return (0);
	while (p_arg[i])
	{
		if (!strcmp(p_arg[i], str)) //Je cherche le charactère *str (qui sera ';' ou "|" selon le cas)
			return (i);
		++i;
	}
	return (i);
}