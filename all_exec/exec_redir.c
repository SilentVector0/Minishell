#include "../minishell.h"

void	exec_redir_in(char *file)
{
	int	fd_in;

	fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	exec_redir_out(char *file)
{
	int	fd_out;

	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	exec_redir_append(char *file)
{
	int	fd_app;

	fd_app = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_app == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd_app, STDOUT_FILENO);
	close(fd_app);
}

void	exec_redir_heredoc(t_redir *redir)
{
	if (redir->heredoc_fd == -1)
		exit (1);
	dup2(redir->heredoc_fd, STDIN_FILENO);
	close(redir->heredoc_fd);
}

void	exec_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN)
			exec_redir_in(redir->file);
		else if (redir->type == REDIR_OUT)
			exec_redir_out(redir->file);
		else if (redir->type == REDIR_APPEND)
			exec_redir_append(redir->file);
		else if (redir->type == REDIR_HEREDOC)
			exec_redir_heredoc(redir);
		redir = redir->r_next;
	}
}
