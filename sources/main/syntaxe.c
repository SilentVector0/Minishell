/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:33:15 by aroduit           #+#    #+#             */
/*   Updated: 2026/05/13 14:33:18 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	verif_out_and_append(t_token *token, t_shell *shell, int nb, char *imput)
{
	if (token[nb].type == TOKEN_OUT || token[nb].type == TOKEN_APPEND)
	{
		nb++;
		if (token[nb].type != TOKEN_WORD)
		{
			free_token(imput, token);
			ft_putstr_fd("minishell: syntax error near\
				unexpected token « newline »\n", 2);
			shell->exit_status = 2;
			return (1);
		}
	}
	return (0);
}

int	verif_in_and_heredoc(t_token *token, t_shell *shell, int nb, char *imput)
{
	if (token[nb].type == TOKEN_IN || token[nb].type == TOKEN_HEREDOC)
	{
		nb++;
		if (token[nb].type != TOKEN_WORD)
		{
			free_token(imput, token);
			ft_putstr_fd("minishell: syntax error near\
				unexpected token « newline »\n", 2);
			shell->exit_status = 2;
			return (1);
		}
	}
	return (0);
}

int	verif_pipe(t_token *token, t_shell *shell, char *imput, int nb)
{
	if (token[0].type == TOKEN_PIPE)
	{
		free_token(imput, token);
		ft_putstr_fd("minishell: syntax error near\
			unexpected token « | »\n", 2);
		shell->exit_status = 2;
		return (1);
	}
	if (token[nb].type == TOKEN_PIPE)
	{
		nb++;
		if (token[nb].type == TOKEN_PIPE || token[nb].type == TOKEN_END)
		{
			free_token(imput, token);
			ft_putstr_fd("minishell: syntax error near\
				unexpected token « | »\n", 2);
			shell->exit_status = 2;
			return (1);
		}
	}
	return (0);
}

int	verif_syntax(char *imput, t_token *token, t_shell *shell)
{
	int	nb;

	nb = 0;
	while (token[nb].type != TOKEN_END)
	{
		if (verif_out_and_append(token, shell, nb, imput) == 1)
			return (1);
		else if (verif_pipe(token, shell, imput, nb) == 1)
			return (1);
		else if (verif_in_and_heredoc(token, shell, nb, imput) == 1)
			return (1);
		nb++;
	}
	return (0);
}
