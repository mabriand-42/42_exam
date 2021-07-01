/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:07:34 by mabriand          #+#    #+#             */
/*   Updated: 2021/07/01 19:16:39 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

static void	ft_cd(char **cmd)
{
	if (!cmd[1] || cmd[2]) //Je regarde s'il n'y a bien qu'un seul argument après la commande 'cd'
		return (ft_error("error: cd: bad arguments\n"));
	if (chdir(cmd[1]) < 0)
	{
		ft_error("error: cd: cannot change directory to ");
		ft_error(cmd[1]);
		ft_error("\n");
	}
	return ;
}

static char	**ft_addCmd(char **av, int *i)
{
	int		size;
	char	**cmd;
	int		j;


	size = ft_cmdSize(&av[*i], ";"); //Je calcule la taille de la commande
	if (!size)
		return (NULL);
	cmd = (char **)malloc(sizeof(char *) * (size + 1)); //J'alloue l'espace nécessaire pour isoler la commande passée en argument
	if (!cmd)
		ft_fatal();
	j = 0;
	while (j < size) //Je stocke la commande
	{
		cmd[j] = av[j + *i];
		++j;
	}
	cmd[j] = NULL;
	*i += size; //J'incrémente *i de la taile de la commande pour passer à la suivante de retour dans la boucle du main()
	return (cmd); //Je retourne la commande isolée et stockée : prête à être traitée
}

int	main(int ac, char **av, char **env)
{
	char **cmd;
	int i;

	cmd = NULL;
	i = 1;
	while (i < ac)
	{
		cmd = ft_addCmd(av, &i); //Je stocke la commande
		if (cmd != NULL)
		{
			if (!strcmp(cmd[0], "cd")) //S'agit-il de la commande 'cd' ?
				ft_cd(cmd);
			else
				ft_execute(cmd, env);
		}
		++i; //Je passe a la commande suivante jusqu'à qu'il ne reste plus d'arguments
	}
	return (0);
}