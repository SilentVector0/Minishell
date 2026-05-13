/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:50:44 by aroduit           #+#    #+#             */
/*   Updated: 2026/05/13 15:50:50 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	count_new(char *content)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
		{
			quote = content[i++];
			while (content[i] && quote != content[i])
			{
				count++;
				i++;
			}
			i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*filter_dup(char *content)
{
	char	*res;
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	res = malloc(sizeof(char) * count_new(content) + 1);
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
		{
			quote = content[i++];
			while (content[i] && content[i] != quote)
				res[count++] = content[i++];
			i++;
		}
		else
		{
			res[count++] = content[i++];
		}
	}
	res[count] = '\0';
	return (res);
}

void	init_var(t_var *var)
{
	var->i = 0;
	var->len = 0;
	var->tmp = NULL;
	var->var = NULL;
}
