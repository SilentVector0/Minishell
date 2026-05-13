/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:38:38 by aroduit           #+#    #+#             */
/*   Updated: 2026/05/13 15:38:38 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

void	case_error(char *imput, t_token *token,
	char *message_erroor)
{
	int	i;
	int	nb_token;

	nb_token = how_many_tokens(imput);
	i = 0;
	while (i < nb_token)
	{
		free(token[i].content);
		i++;
	}
	free(token);
	free(imput);
	printf("%s\n", message_erroor);
}

void	case_continue(char *imput, t_token *token, char *message_erroor)
{
	free(token);
	free(imput);
	printf("%s\n", message_erroor);
}
