/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:31:17 by aroduit           #+#    #+#             */
/*   Updated: 2026/06/10 12:00:30 by msuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	child_process(t_parser *current, int fd[2], int *prev_fd, t_shell *shell)
{
	int	exit_code;

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
	{
		exit_code = exec_builtin(current, shell);
		free_all(current, shell);
		exit (exit_code);
	}
	if (!current->cmd || get_exec(current, shell))
		exit(127);
	execve(current->path, current->arg, shell->envp);
	return (after_exc(current, shell), 0);
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
		free_parser(current);
		exit(126);
	}
	else
	{
		if (access(current->path, F_OK) == 0)
		{
			ft_putstr_fd(current->path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			free_parser(current);
			exit(126);
		}
	}
	perror(current->cmd);
	free_parser(current);
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
