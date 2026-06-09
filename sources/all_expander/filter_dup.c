/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:52:52 by aroduit           #+#    #+#             */
/*   Updated: 2026/06/09 15:52:52 by aroduit          ###   ####lausanne.ch   */
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

char	**build_new_arg(char **old_arg, char **split, int j)
{
	char	**new_arg;
	int		old_len;
	int		split_len;
	int		k;
	int		i;

	split_len = 0;
	while (split[split_len])
		split_len++;
	old_len = 0;
	while (old_arg[old_len])
		old_len++;
	new_arg = malloc(sizeof(char *) * (old_len + split_len));
	k = 0;
	i = 0;
	while (i < j)
		new_arg[k++] = old_arg[i++];
	i = 0;
	while (split[i])
		new_arg[k++] = split[i++];
	i = j + 1;
	while (old_arg[i])
		new_arg[k++] = old_arg[i++];
	new_arg[k] = NULL;
	return (new_arg);
}

void	split_arg(t_parser *parser, int j)
{
	char	**split;
	char	**new_arg;

	split = ft_split(parser->arg[j], ' ');
	new_arg = build_new_arg(parser->arg, split, j);
	free(split);
	free(parser->arg[j]);
	free(parser->arg);
	parser->arg = new_arg;
}
