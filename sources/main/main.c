#include "includes/minishell.h"

int	g_signal = 0;

void	exit_d(t_shell *shell)
{
	write(1, "exit\n", 5);
	free_shell(shell);
	exit(0);
}

void	free_each_loop(char *imput, t_token *token, t_parser *parser)
{
	free_token(imput, token);
	free_parser(parser);
}

void	init(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	if (!envp[i])
	{
		shell->envp = malloc(sizeof(char *) * 2);
		shell->envp[0] = ft_strdup("SHLVL=0");
		shell->envp[1] = NULL;
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

int	main(int argc, char **argv, char **envp)
{
	t_token		*token;
	t_parser	*parser;
	char		*imput;
	t_shell		*shell;

	(void)argc;
	(void)argv;
	shell = init_my_tshell(envp);
	token = NULL;
	parent_signals();
	while (1)
	{
		imput = readline("minishell>");
		if (!imput)
			exit_d(shell);
		add_history(imput);
		if (verif_imput_and_parser(imput, &token, shell) != 0)
			continue ;
		parser = create_parser(token);
		if (parser != NULL)
			if (parser_diff_null(parser, shell, token, imput) != 0)
				continue ;
		free_each_loop(imput, token, parser);
	}
	free_shell(shell);
}
