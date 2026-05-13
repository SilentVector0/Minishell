/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:32:00 by aroduit           #+#    #+#             */
/*   Updated: 2026/05/13 14:32:02 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_env(t_shell *shell)
{
	int	i;

	if (!shell->envp)
		return (1);
	i = -1;
	while (shell->envp[++i])
	{
		ft_putstr_fd(shell->envp[i], 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
