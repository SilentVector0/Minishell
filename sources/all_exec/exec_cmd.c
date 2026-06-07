/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 09:29:24 by aroduit           #+#    #+#             */
/*   Updated: 2026/06/07 09:29:29 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	fork_pipeline(t_parser *parser, int *prev_fd,
	t_shell *shell, pid_t *last_pid)
{
	t_parser	*current;
	pid_t		pid;
	int			fd[2];

	current = parser;
	while (current)
	{
		if (current->next && pipe(fd) == -1)
			return (perror_return("pipe", 1));
		pid = fork();
		if (pid == -1)
			return (perror_return("fork", 1));
		if (!pid)
			child_process(current, fd, prev_fd, shell);
		else
			parent_process(current, fd, prev_fd);
		if (!current->next)
			*last_pid = pid;
		current = current->next;
	}
	return (0);
}

int	wait_pipeline(pid_t *last_pid)
{
	pid_t		waited;
	int			status;
	int			last_status;

	status = 0;
	last_status = 0;
	waited = waitpid(-1, &status, 0);
	while (waited > 0)
	{
		if (waited == *last_pid)
			last_status = status;
		waited = waitpid(-1, &status, 0);
	}
	return (last_status);
}

int	execute_pipeline(t_parser *parser, int *prev_fd, t_shell *shell)
{
	pid_t		last_pid;
	int			last_status;

	last_pid = -1;
	signal(SIGINT, SIG_IGN);
	if (fork_pipeline(parser, prev_fd, shell, &last_pid))
		return (1);
	last_status = wait_pipeline(&last_pid);
	parent_signals();
	if (WIFSIGNALED(last_status))
	{
		if (WTERMSIG(last_status) == SIGINT)
			write(1, "\n", 1);
		return (128 + WTERMSIG(last_status));
	}
	return (WEXITSTATUS(last_status));
}

int	get_exec(t_parser *parser, t_shell *shell)
{
	if (ft_strchr(parser->cmd, '/'))
		parser->path = ft_strdup(parser->cmd);
	else
		parser->path = get_path(parser->cmd, shell->envp);
	if (!parser->path)
	{
		ft_putstr_fd(parser->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_parser(parser);
		free_shell(shell);
		return (127);
	}
	return (0);
}

int	execute_cmd(t_parser *parser, t_shell *shell)
{
	int	prev_fd;

	prev_fd = -1;
	if (prepare_heredocs(parser, shell))
	{
		if (g_signal == SIGINT)
			shell->exit_status = 130;
		else
			shell->exit_status = 1;
		return (1);
	}
	if (is_builtin(parser) && parser->next == NULL && parser->redir == NULL)
	{
		shell->exit_status = exec_builtin(parser, shell);
		return (shell->exit_status);
	}
	shell->exit_status = execute_pipeline(parser, &prev_fd, shell);
	if (prev_fd != -1)
		close (prev_fd);
	return (shell->exit_status);
}
