/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:06:52 by msuter            #+#    #+#             */
/*   Updated: 2026/03/01 14:07:45 by msuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

void	case_error(char *imput, t_token *token,
	char *message_erroor, int nb_token)
{
	int	i;

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
	exit(1);
}

void	case_continue(char *imput, t_token *token, char *message_erroor)
{
	free(token);
	free(imput);
	printf("%s\n", message_erroor);
}

void	end_prog(char *imput, t_token *token, int nb_token)
{
	int	i;

	nb_token = how_many_tokens(imput);
	i = 0;
	while (i < nb_token)
	{
		free(token[i].content);
		i++;
	}
	free(token);
	free(imput);
	exit (0);
}

void	free_token(char *imput, t_token *token, int nb_token)
{
	int	i;

	nb_token = how_many_tokens(imput);
	i = 0;
	while (i < nb_token)
	{
		free(token[i].content);
		i++;
	}
	free(token);
	free(imput);
}
