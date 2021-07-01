/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:07:34 by mabriand          #+#    #+#             */
/*   Updated: 2021/07/01 17:54:59 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

int	ft_cmdSize(char **p_arg, char *str) //Il s'agit d'arguments d'où la '*' supplémentaire car av = tab[ac] de pointeurs
{											//=>	cd folder = "cd" "folder"
	int	i;									//=>	echo something ; echo something else = "echo" "something" ";" "echo" "something" "else"

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

static char	**ft_findPipe(char **cmd)
{
	int i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		if (!strcmp(cmd[i], "|"))
			return (&cmd[i + 1]);
		++i;
	}
	return (NULL);
}

void	ft_exeCmd(char **cmd, char **env)
{
	pid_t	pid;
	if ((pid = fork()) < 0)
		ft_fatal();
	if (!pid) //Si on est dans le processus fils
	{
		if (execve(cmd[0], cmd, env) < 0)
		{
			ft_error("error: cannot execute ");
			ft_error(cmd[0]);
			ft_error("\n");
			exit(1);
		}
	}
	waitpid(0, NULL, 0); //Si on est dans le processus père, on attend que le fils soit terminé
	return ;
}

void	ft_son(char **cmd, char **env, int fd_in, int *fd_0, int *fd_1)
{
	if (dup2(fd_in, STDIN_FILENO) < 0)
		ft_fatal();
	if (ft_findPipe(cmd))
	{
		if (dup2(*fd_1, STDOUT_FILENO) < 0)
			ft_fatal();
	}
	close(fd_in);
	close(*fd_0);
	close(*fd_1);
	cmd[ft_cmdSize(cmd, "|")] = NULL;
	ft_exeCmd(cmd, env);
	exit(0);
}

// void	ft_parent(char **cmd, int fd_in, int *fd_0, int *fd_1, int *nb_wait)
// {
// 	if (dup2(*fd_0, fd_in) < 0)
// 		ft_fatal();
// 	close(*fd_0);
// 	close(*fd_1);
// 	(*nb_wait)++;
// 	cmd = ft_findPipe(cmd);
// 	return ;
// }

void	ft_execute(char **cmd, char **env)
{
	//S'il la commande ne contient pas de pipe
	if (!ft_findPipe(cmd))
		return (ft_exeCmd(cmd, env));
	//S'il la commande contient un ou plusieurs pipe(s)
	int		fd_in;
	int		fd_pipe[2];
	int		nb_wait = 0;
	pid_t	pid;

	if ((fd_in = dup(STDIN_FILENO)) < 0) //Je sauvegarde STDIN_FILENO dans fd_in
		ft_fatal();
	while(cmd)
	{
		if (pipe(fd_pipe) < 0 || (pid = fork()) < 0)
		{
			ft_error("error: fatal\n");
			exit(1);
		}
		if (!pid)
		{
			if (dup2(fd_in, STDIN_FILENO) < 0)
				ft_fatal();
			if (ft_findPipe(cmd))
			{
				if (dup2(fd_pipe[1], STDOUT_FILENO) < 0)
					ft_fatal();
			}
			close(fd_in);
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			cmd[ft_cmdSize(cmd, "|")] = NULL;
			ft_exeCmd(cmd, env);
			exit(0);
		}	//ft_son(cmd, env, fd_in, &fd_pipe[0], &fd_pipe[1]);
		else
		{
			if (dup2(fd_pipe[0], fd_in) < 0)
				ft_fatal();
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			nb_wait++;
			cmd = ft_findPipe(cmd);
		}	//ft_parent(cmd, fd_in, &fd_pipe[0], &fd_pipe[1], &nb_wait);
	}
	close(fd_in);
	while (nb_wait >= 0)
	{
		waitpid(0, NULL, 0);
		--nb_wait;
	}
	return ;
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