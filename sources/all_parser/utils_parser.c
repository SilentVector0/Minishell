/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:31:06 by aroduit           #+#    #+#             */
/*   Updated: 2026/05/13 14:31:07 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	pass_word(int *temp, int *count, t_token *token)
{
	while (token[*temp].type != TOKEN_END && token[*temp].type != TOKEN_PIPE)
	{
		if (is_redirect(token, temp))
			*temp += 2;
		else if (token[*temp].type == TOKEN_WORD)
		{
			(*temp)++;
			(*count)++;
		}
		else
			(*temp)++;
	}
}

void	attrib_pipe(t_parser **current, t_redir **current_redir, int *nb)
{
	(*current)->next = new_node();
	(*current) = (*current)->next;
	(*current_redir) = NULL;
	(*nb)++;
}

void	attrib_redir(t_parser *current, t_redir\
	**current_redir, t_token *token, int *nb)
{
	if (current->redir == NULL)
	{
		current->redir = which_type(token, nb);
		(*current_redir) = current->redir;
	}
	else
	{
		(*current_redir)->r_next = which_type(token, nb);
		(*current_redir) = (*current_redir)->r_next;
	}
}

int	is_redirect(t_token *token, int	*nb)
{
	if (token[*nb].type == TOKEN_IN || token[*nb].type == TOKEN_OUT
		|| token[*nb].type == TOKEN_APPEND || token[*nb].type == TOKEN_HEREDOC)
		return (1);
	return (0);
}
