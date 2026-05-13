/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:38:58 by aroduit           #+#    #+#             */
/*   Updated: 2026/05/13 15:39:28 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	case_d_quote(char *imput, t_contexte *c)
{
	c->i++;
	while (imput[c->i] && imput[c->i] != '\"')
		c->i++;
	if (imput[c->i] == '\"')
	{
		c->i++;
		while (imput[c->i] && !is_space(imput[c->i])
			&& imput[c->i] != '|' && imput[c->i] != '<' && imput[c->i] != '>'
			&& imput[c->i] != '\'' && imput[c->i] != '\"')
			c->i++;
		return (0);
	}
	return (-1);
}

static int	case_quote(char *imput, t_contexte *c)
{
	c->i++;
	while (imput[c->i] && imput[c->i] != '\'')
		c->i++;
	if (imput[c->i] == '\'')
	{
		c->i++;
		while (imput[c->i] && !is_space(imput[c->i])
			&& imput[c->i] != '|' && imput[c->i] != '<' && imput[c->i] != '>'
			&& imput[c->i] != '\'' && imput[c->i] != '\"')
			c->i++;
		return (0);
	}
	return (-1);
}

static int	mid(char *imput, t_contexte *c)
{
	while (is_space(imput[c->i]) == 1)
		c->i++;
	if (imput[c->i] == '\0')
		return (0);
	if (imput[c->i] == '\'')
	{
		if (case_quote(imput, c) == -1)
			return (-1);
	}
	else if (imput[c->i] == '\"')
	{
		if (case_d_quote(imput, c) == -1)
			return (-1);
	}
	else if (imput[c->i] == '|' || imput[c->i] == '<' || imput[c->i] == '>')
		c->i++;
	else
		while (imput[c->i] && !is_space(imput[c->i])
			&& imput[c->i] != '|' && imput[c->i] != '<' && imput[c->i] != '>'
			&& imput[c->i] != '\'' && imput[c->i] != '\"')
			c->i++;
	return (0);
}

int	how_many_tokens(char *imput)
{
	t_contexte	c;
	int			res;

	c.i = 0;
	c.nb = 0;
	while (imput[c.i])
	{
		res = mid(imput, &c);
		if (res == -1)
		{
			free(imput);
			printf("quote manquante\n");
			return (-1);
		}
		c.nb++;
	}
	return (c.nb);
}
