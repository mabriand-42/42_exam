/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:20:02 by mabriand          #+#    #+#             */
/*   Updated: 2021/07/01 18:25:03 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

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

static void	ft_exeCmd(char **cmd, char **env)
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

static void	ft_son(char **cmd, char **env, int fd_in, int *fd_0, int *fd_1)
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

static void	ft_parent(char **cmd, int fd_in, int *fd_0, int *fd_1, int *nb_wait)
{
	if (dup2(*fd_0, fd_in) < 0)
		ft_fatal();
	close(*fd_0);
	close(*fd_1);
	(*nb_wait)++;
	cmd = ft_findPipe(cmd);
	return ;
}

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
			ft_son(cmd, env, fd_in, &fd_pipe[0], &fd_pipe[1]);
		else
			ft_parent(cmd, fd_in, &fd_pipe[0], &fd_pipe[1], &nb_wait);
	}
	close(fd_in);
	while (nb_wait >= 0)
	{
		waitpid(0, NULL, 0);
		--nb_wait;
	}
	return ;
}