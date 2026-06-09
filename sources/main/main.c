/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:23:55 by aroduit           #+#    #+#             */
/*   Updated: 2026/06/09 15:24:03 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal = 0;

int	exit_shell(t_shell *shell)
{
	int	exit_code;

	if (shell->interactive)
		write(1, "exit\n", 5);
	exit_code = shell->exit_status;
	free_shell(shell);
	exit(exit_code);
}

void	init(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	if (!envp[i])
	{
		shell->envp = malloc(sizeof(char *) * 3);
		shell->envp[0] = ft_strdup("SHLVL=0");
		shell->envp[1] = ft_strdup("PATH=/bin:/usr/bin");
		shell->envp[2] = NULL;
		return ;
	}
	while (envp[i])
		i++;
	shell->envp = malloc (sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
	shell->exit_status = 0;
	shell->interactive = isatty(STDIN_FILENO);
	shell->line_num = 0;
}

t_shell	*init_my_tshell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	init(shell, envp);
	increm_lvl(shell);
	return (shell);
}

void	run_shell(t_shell *shell)
{
	t_token		*token;
	t_parser	*parser;
	char		*imput;

	token = NULL;
	while (1)
	{
		imput = readline("minishell>");
		if (!imput)
			exit_shell(shell);
		if (shell->interactive)
			add_history(imput);
		if (verif_imput_and_parser(imput, &token, shell) != 0)
			continue ;
		parser = create_parser(token, imput);
		if (parser == NULL)
			continue ;
		parser_diff_null(parser, shell);
		free_parser(parser);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;

	(void)argc;
	(void)argv;
	shell = init_my_tshell(envp);
	parent_signals();
	run_shell (shell);
	return (0);
}
