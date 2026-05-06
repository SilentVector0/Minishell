#include "../minishell.h"

static int	which_case(char *imput, t_contexte *c, t_token *token)
{
	int	verif_quote;

	verif_quote = 0;
	if (imput[c->i] == '|')
	{
		token[c->nb].type = TOKEN_PIPE;
		token[c->nb].content = NULL;
		c->nb++;
		c->i++;
	}
	else if (imput[c->i] == '>')
		case_out_or_happend(imput, c, token);
	else if (imput[c->i] == '<')
		case_in_or_heredoc(imput, c, token);
	else
		verif_quote = case_word(imput, c);
	return (verif_quote);
}

void	verif_type_quote(char *imput, t_contexte *c, char quote)
{
	c->size_word++;
	while (imput[c->i + c->size_word]
		&& imput[c->i + c->size_word] != quote)
		c->size_word++;
	if (imput[c->i + c->size_word] == quote)
		c->size_word++;
}

void	create_new_token(t_token *token, char *imput, t_contexte *c)
{
	token[c->nb].content = malloc(sizeof(char) * c->size_word + 1);
	ft_strlcpy(token[c->nb].content, imput + c->i, c->size_word + 1);
	token[c->nb].type = TOKEN_WORD;
	c->nb++;
	c->i += c->size_word;
	c->size_word = 0;
}

static int	set_token(char *imput, t_token *token, t_contexte *c)
{
	while (is_space(imput[c->i]))
		c->i++;
	if (imput[c->i] == '|' || imput[c->i] == '<' || imput[c->i] == '>')
	{
		which_case(imput, c, token);
		return (0);
	}
	while (imput[c->i + c->size_word] && !is_space(imput[c->i + c->size_word])
		&& imput[c->i + c->size_word] != '|'
		&& imput[c->i + c->size_word] != '<'
		&& imput[c->i + c->size_word] != '>')
	{
		if (imput[c->i + c->size_word] == '\'')
			verif_type_quote(imput, c, '\'');
		else if (imput[c->i + c->size_word] == '\"')
			verif_type_quote(imput, c, '\"');
		else
			c->size_word++;
	}
	if (c->size_word > 0)
		create_new_token(token, imput, c);
	return (0);
}

t_token	*lexing(char *imput, int verif_nb)
{
	t_contexte	c;
	t_token		*token;

	c.nb = 0;
	c.i = 0;
	c.size_word = 0;
	if (verif_nb == -1)
		return (NULL);
	token = malloc(sizeof(t_token) * (verif_nb + 1));
	if (!token)
		case_error(imput, token, "erreur lors du malloc du token");
	while (imput[c.i])
	{
		if (set_token(imput, token, &c) == 1)
			return (token);
	}
	token[c.nb].type = TOKEN_END;
	return (token);
}
