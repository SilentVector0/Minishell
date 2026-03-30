/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 10:02:49 by msuter            #+#    #+#             */
/*   Updated: 2026/03/14 15:56:05 by msuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	set_token(char *imput, t_token *token, t_contexte *c)
{
	while (is_space(imput[c->i]))
		c->i++;
	which_case(imput, c, token);
	if (c->size_word > 0 && (imput[c->i + c->size_word] == '\0'
			|| imput[c->i + c->size_word] == ' '
			|| imput[c->i + c->size_word] == '|'
			|| imput[c->i + c->size_word] == '<'
			|| imput[c->i + c->size_word] == '>'))
	{
		token[c->nb].content = malloc(sizeof(char) * c->size_word + 1);
		ft_strlcpy(token[c->nb].content, imput + c->i, c->size_word + 1);
		token[c->nb].type = TOKEN_WORD;
		c->nb++;
		if (imput[c->size_word - 1] == '\0')
			return (1);
		c->i += c->size_word;
		c->size_word = 0;
	}
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
		case_error(imput, token, "erreur lors du malloc du token", verif_nb);
	while (imput[c.i])
	{
		if (set_token(imput, token, &c) == 1)
			return (token);
	}
	token[c.nb].type = TOKEN_END;
	return (token);
}
