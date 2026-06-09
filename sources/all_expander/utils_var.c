/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:11:45 by aroduit           #+#    #+#             */
/*   Updated: 2026/06/09 16:14:24 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_my_var(t_parser *parser, t_var *var)
{
	var->var = ft_strdup(parser->arg[var->j]);
	free(parser->arg[var->j]);
	parser->arg[var->j] = filter_dup(var->var);
	free (var->var);
	var->var = NULL;
	var->j++;
}

void	init_var(t_var *var)
{
	var->i = 0;
	var->len = 0;
	var->tmp = NULL;
	var->var = NULL;
}

void	process_arg(t_parser *parser, t_shell *shell, t_var *var)
{
	init_var (var);
	while (parser->arg[var->j][var->i])
	{
		if (verif_and_schr_in_env(parser, var, shell) == 1)
			break ;
	}
	if (var->tmp != NULL)
	{
		replace(parser, var->tmp, var->j, var->len);
		free(var->tmp);
		var->tmp = NULL;
		if (ft_strchr(parser->arg[var->j], ' '))
			split_arg(parser, var->j);
		return ;
	}
	if (parser->arg[var->j][var->i] == '\0')
		free_my_var(parser, var);
}
