/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_chained.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:37:10 by msuter            #+#    #+#             */
/*   Updated: 2026/03/20 15:39:39 by msuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*new_redir_node(void)
{
	t_redir *redir;

	redir = malloc(sizeof(t_parser));
	if (!redir)
		return (NULL);
	redir = ft_memset(redir, 0, sizeof(t_parser));
	return (redir);
}

t_redir	*attach_redir_node(t_redir *current)
{
	t_redir *new = new_redir_node();

	current->r_next = new;
	return (new);
}