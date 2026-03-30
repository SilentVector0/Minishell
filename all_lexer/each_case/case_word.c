/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:07:14 by msuter            #+#    #+#             */
/*   Updated: 2026/03/01 14:06:37 by msuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	case_single_quote(char *imput, t_contexte *c)
{
	int	temp;

	temp = c->i + c->size_word;
	while (imput[temp] && imput[temp] != '\'')
	{
		c->size_word++;
		temp++;
		if (imput[temp] == '\'')
		{
			(c->size_word)++;
			return (0);
		}
	}
	return (-1);
}

static int	case_double_quote(char *imput, t_contexte *c)
{
	int	temp;

	temp = c->i + c->size_word;
	while (imput[temp] && imput[temp] != '\"')
	{
		c->size_word++;
		temp++;
		if (imput[temp] == '\"')
		{
			c->size_word++;
			return (0);
		}
	}
	return (-1);
}

static int	case_no_quotes(char *imput, t_contexte *c)
{
	int	temp;

	temp = c->i + c->size_word;
	while (imput[temp] && imput[temp] != ' ' && imput[temp] != '|'
		&& imput[temp] != '<' && imput[temp] != '>')
	{
		c->size_word++;
		temp++;
	}
	return (0);
}

int	case_word(char *imput, t_contexte *c)
{
	int	temp;

	temp = c->i + c->size_word;
	if (imput[temp] == '\'')
	{
		c->size_word++;
		if (case_single_quote(imput, c) == 0)
			return (0);
	}
	else if (imput[temp] == '\"')
	{
		c->size_word++;
		if (case_double_quote(imput, c) == 0)
			return (0);
	}
	else
	{
		case_no_quotes(imput, c);
		return (0);
	}
	return (-1);
}
