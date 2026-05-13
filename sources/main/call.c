/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:34:05 by aroduit           #+#    #+#             */
/*   Updated: 2026/05/13 14:34:05 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	filter_my_arg(t_parser *current)
{
	int		i;
	int		len;
	char	*tmp;
	char	*a;

	i = 0;
	while (current->arg[i])
	{
		a = current->arg[i];
		len = ft_strlen(a);
		if (len >= 2 && ((a[0] == '"' && a[len -1] == '"')
				|| (a[0] == '\'' && a[len -1] == '\'')))
		{
			tmp = filter_dup(current->arg[i]);
			free(current->arg[i]);
			current->arg[i] = tmp;
		}
		i++;
	}
}

void	filter_all_args(t_parser *parser)
{
	t_parser	*current;
	char		*tmp;

	current = parser;
	while (current)
	{
		if (current->arg)
			filter_my_arg(current);
		if (current->cmd)
		{
			if (ft_strchr(current->cmd, '\'') || ft_strchr(current->cmd, '\"'))
			{
				tmp = filter_dup(current->cmd);
				free(current->cmd);
				current->cmd = tmp;
			}
		}
		current = current->next;
	}
}

int	commande_null(t_parser *parser, t_shell *shell)
{
	int	i;

	i = 0;
	if (parser->arg && parser->arg[1])
	{
		free(parser->arg[0]);
		while (parser->arg[i + 1])
		{
			parser->arg[i] = parser->arg[i + 1];
			i++;
		}
		parser->arg[i] = NULL;
		free(parser->cmd);
		parser->cmd = ft_strdup(parser->arg[0]);
	}
	else
	{
		shell->exit_status = 0;
		return (0);
	}
	return (1);
}

int	parser_diff_null(t_parser *parser, t_shell *shell,
	t_token *token, char *imput)
{
	search_var(parser, shell);
	filter_all_args(parser);
	if (parser->arg && parser->arg[0])
	{
		free(parser->cmd);
		parser->cmd = ft_strdup(parser->arg[0]);
	}
	if (parser->cmd && parser->cmd[0] == '\0')
		if (commande_null(parser, shell) == 0)
			return (0);
	execute_cmd(parser, shell, token, imput);
	return (0);
}

int	verif_imput_and_parser(char *imput, t_token **token, t_shell *shell)
{
	int	i;

	i = 0;
	if (imput[0] == '\0')
	{
		free(imput);
		return (1);
	}
	i = how_many_tokens(imput);
	if (i == -1)
		return (1);
	*token = lexing(imput, i);
	if (verif_syntax(imput, *token, shell) == 1)
		return (1);
	if (*token == NULL)
	{
		case_continue(imput, *token, "erreur, il manque une quote");
		return (1);
	}
	return (0);
}
