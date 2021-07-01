#include "../microshell.h"


void	ft_cd(char **cmd)
{
	if (!cmd[1] || cmd[2])//if (!cmd)
		return (ft_error("error: cd: bad arguments\n"));//ft_error();
	if (chdir(cmd[1]) < 0)
	{
		ft_error("error: cd: cannot change directory to ");
		ft_error(cmd[1]);//ft_error(cmd[0]);
		ft_error("\n");
	}
	return ;
}

char **ft_addCmd(char **av, int *i)
{
	int		size;
	char	**cmd;
	int		j;

	size = ft_cmdSize(&av[*i], ";");
	if (!size)
		return (NULL);
	cmd = (char **)sizeof(char *) * size + 1);
	if (!cmd)
		ft_fatal();//return (NULL);
	j = 0;
	while (j < size)
	{
		cmd[j] = av[j + *i];//av[j];
		++j;
	}
	cmd[j] = NULL;//
	*i += size;
	return (cmd);
}

int main(int ac, char **av, char **env)
{
	char	**cmd;
	int		i;

	cmd = NULL;
	i = 1;
	while (i < ac)
	{
		cmd = ft_addCmd(av, &i);
		if (cmd != NULL)
		{
			if (!strcmp(cmd[i]), "cd")
				ft_cd(cmd);//ft_cd();
			else
				ft_execute(cmd, env);//ft_execute();
		}
		++i;
	}
	return (0);
}