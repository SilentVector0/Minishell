
#include "../minishell.h"

static int	case_hapend(char *imput, t_contexte *c, t_token *token)
{
	if (imput[c->i + 1] == '>')
	{
		c->i += 2;
		token[c->nb].type = TOKEN_APPEND;
		token[c->nb].content = NULL;
		c->nb++;
		return (1);
	}
	return (0);
}

void	case_out_or_happend(char *imput, t_contexte *c, t_token *token)
{
	if (case_hapend(imput, c, token) == 1)
		return ;
	token[c->nb].type = TOKEN_OUT;
	token[c->nb].content = NULL;
	c->nb++;
	c->i++;
}

static int	case_heredoc(char *imput, t_contexte *c, t_token *token)
{
	if (imput[c->i + 1] == '<')
	{
		c->i += 2;
		token[c->nb].type = TOKEN_HEREDOC;
		token[c->nb].content = NULL;
		c->nb++;
		return (1);
	}
	return (0);
}

void	case_in_or_heredoc(char *imput, t_contexte *c, t_token *token)
{
	if (case_heredoc(imput, c, token) == 1)
		return ;
	token[c->nb].type = TOKEN_IN;
	token[c->nb].content = NULL;
	c->nb++;
	c->i++;
}
