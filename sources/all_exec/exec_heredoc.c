/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 18:03:06 by aroduit           #+#    #+#             */
/*   Updated: 2026/05/31 18:03:06 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	close_unused_heredocs(t_redir *redir)
{
	t_redir	*tmp;
	t_redir	*last_heredoc;

	last_heredoc = NULL;
	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
			last_heredoc = tmp;
		tmp = tmp->r_next;
	}
	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC && tmp != last_heredoc)
		{
			if (tmp->type == REDIR_HEREDOC && tmp != last_heredoc)
			{
				close (tmp->heredoc_fd);
				tmp->heredoc_fd = -1;
			}
		}
		tmp = tmp->r_next;
	}
}

void	warning_msg_heredoc(t_redir	*redir, int line_num)
{
	char	*num;

	num = ft_itoa(line_num);
	if (!num)
	{
		ft_putstr_fd("warning: here-document \
			delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd("')\n", 2);
		return ;
	}
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putstr_fd(num, 2);
	free (num);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(redir->file, 2);
	ft_putstr_fd("')\n", 2);
}

void	heredoc_loop(int fd, t_redir *redir, t_shell *shell)
{
	char	*line;
	int		line_num;

	line_num = shell->line_num;
	while (1)
	{
		line = readline("> ");
		shell->line_num++;
		if (!line)
		{
			if (g_signal != SIGINT)
				warning_msg_heredoc (redir, line_num);
			break ;
		}
		if (ft_strcmp (line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	prepare_one_heredoc(t_redir *redir, t_shell *shell)
{
	int		fd[2];
	int		stdin_copy;

	if (pipe(fd) == -1)
		return (perror_return("pipe", 2));
	stdin_copy = dup(STDIN_FILENO);
	g_signal = 0;
	signal(SIGINT, handle_heredoc_sigint);
	heredoc_loop(fd[1], redir, shell);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	signal(SIGINT, handle_sigint);
	close(fd[1]);
	if (g_signal == SIGINT)
	{
		close(fd[0]);
		shell->exit_status = 130;
		return (1);
	}
	redir->heredoc_fd = fd[0];
	return (0);
}

int	prepare_heredocs(t_parser *parser, t_shell *shell)
{
	t_parser	*current;
	t_redir		*redir;

	current = parser;
	while (current)
	{
		redir = current->redir;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				if (prepare_one_heredoc(redir, shell))
					return (1);
			}
			redir = redir->r_next;
		}
		current = current->next;
	}
	return (0);
}
