#include "../minishell.h"

void    free_redir(t_parser *parser)
{
	t_redir	*tmp;

	while (parser->redir)
	{
		if (parser->redir->file)
			free (parser->redir->file);
		tmp = parser->redir;
		parser->redir = parser->redir->r_next;
		free (tmp);
	}
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

void	free_parser(t_parser *parser)
{
	t_parser	*tmp;

	while (parser)
	{
		if (parser->redir)
			free_redir(parser);
		if (parser->arg)
			free_tab(parser);
		if (parser->cmd)
			free (parser->cmd);
		tmp = parser;
		parser = parser->next;
		free (tmp);
	}
}

int	perror_return(char *msg, int ret)
{
	perror(msg);
	return (ret);
}