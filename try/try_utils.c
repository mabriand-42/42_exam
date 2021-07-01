#include "../microshell.h"

static int		ft_strlen(Char *str)
{
	int i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

void	ft_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return ;
}

void	ft_fatal()
{
	ft_error("error: fatal\n");
	exit(1);

}

int		ft_cmdSize(char **p_arg, char *str)
{
	int i;

	i = 0;
	if (!p_arg)
		return (0);
	while (p_arg[i])
	{
		if (!strcmp(p_arg[i], str))
			return (i);
		++i;
	}
	return (i);
}