/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 01:07:32 by aroduit           #+#    #+#             */
/*   Updated: 2026/06/01 01:07:32 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	child_process(t_parser *current, int fd[2], int *prev_fd, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	if (current->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	if (current->redir)
		exec_redir(current->redir);
	if (is_builtin(current))
		exit (exec_builtin(current, shell, NULL, NULL));
	if (!current->cmd || get_exec(current, shell))
		exit(127);
	execve(current->path, current->arg, shell->envp);
	echec_cmd(current);
	exit(127);
}

void	parent_process(t_parser *current, int fd[2], int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

void	echec_cmd(t_parser *current)
{
	if (access(current->path, X_OK) == 0)
	{
		ft_putstr_fd(current->path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	else
	{
		if (access(current->path, F_OK) == 0)
		{
			ft_putstr_fd(current->path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
	}
	perror(current->cmd);
}

void	free_tab(t_parser *parser)
{
	int	i;

	i = -1;
	if (!parser->arg)
		return ;
	while (parser->arg[++i])
		free(parser->arg[i]);
	free (parser->arg);
}

int	perror_return(char *msg, int ret)
{
	perror(msg);
	return (ret);
}
