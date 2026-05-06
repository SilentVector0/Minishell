#include "../minishell.h"

void	echec_cmd(t_parser *current)
{
	if (access(current->path, X_OK) == 0)
	{
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	else
	{
		if (access(current->path, F_OK) == 0)
		{
			ft_putstr_fd(current->path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
	}
	perror(current->cmd);
}

void	free_tab(t_parser *parser)
{
	int	i;

	i = -1;
	if (!parser->arg)
		return ;
	while (parser->arg[++i])
		free(parser->arg[i]);
	free (parser->arg);
}

int	perror_return(char *msg, int ret)
{
	perror(msg);
	return (ret);
}
