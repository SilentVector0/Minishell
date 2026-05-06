#include "../minishell.h"

// void	testing(t_parser *parser)
// {
// 	while (parser != NULL)
// 	{
// 		int i = 0;
// 		printf("\n\n debut de ma boucle while pour les redir\n\n");
// 		while (parser->redir != NULL)
// 		{
// 			printf("\n\nprint de mon type\n\n");
// 			printf("%d\n", parser->redir->type);
// 			printf("\n\nprint de mon file\n\n");
// 			printf("%s\n", parser->redir->file);
// 			printf("nouveau noeud de mon t_redir\n");
// 			parser->redir = parser->redir->r_next;
// 		}
// 		if (parser->cmd != NULL)
// 		{
// 			printf("\n\nprint de ma cmd\n\n");
// 			printf("%s\n", parser->cmd);
// 			printf("\n\n debut de ma boucle while pour les arg\n\n");
// 			while (parser->arg[i] != NULL)
// 			{
// 				printf("\n\nprint de mes arg\n\n");
// 				printf("%s\n", parser->arg[i]);
// 				i++;
// 			}
// 		}
// 		parser = parser->next;
// 	}
// }

void	init(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	if (!envp[i])
	{
		shell->envp = malloc(sizeof(char *) * 2);
		shell->envp[0] = ft_strdup("SHLVL=0");
		shell->envp[1] = NULL;
		return;
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

void    filter_all_args(t_parser *parser)
{
    t_parser    *current;
    int         i;
    char        *tmp;

    current = parser;
    while (current)
    {
        i = 0;
        if (current->arg)
        {
            while (current->arg[i])
            {
                char *a = current->arg[i];
   				int len = ft_strlen(a);
   				if (len >= 2 && ((a[0] == '"' && a[len-1] == '"') 
        			|| (a[0] == '\'' && a[len-1] == '\'')))
    			{
       				tmp = filter_dup(current->arg[i]);
        			free(current->arg[i]);
        			current->arg[i] = tmp;
    			}
    			i++;
            }
        }
        if (current->cmd)
        {
            if (ft_strchr(current->cmd, '\'') || ft_strchr(current->cmd, '\"'))
            {
                tmp = filter_dup(current->cmd);
                free(current->cmd);
                current->cmd = tmp;
            }
        }
        current = current->next;
    }
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*token;
	t_parser	*parser;
	char		*imput;
	int			verif_nb;
	t_shell		*shell;
	int			i;

	shell = malloc(sizeof(t_shell));
	init(shell, envp);
	increm_lvl(shell);
	(void)argc;
	(void)argv;
	while (1)
	{
		imput = readline("minishell>");
		if (!imput)
			case_error(imput, NULL, "erreur lors du malloc du imput", verif_nb);
		add_history(imput);
		if (imput[0] == '\0')
		{
   			free(imput);
    		continue ;
		}
		verif_nb = how_many_tokens(imput);
		token = lexing(imput, verif_nb);
		if (token == NULL)
		{
			case_continue(imput, token, "erreur, il manque une quote");
			continue ;
		}
		parser = create_parser(token);
		// testing(parser);
		if (parser != NULL)
		{
			search_var(parser, shell);
			filter_all_args(parser);
			if (parser->arg && parser->arg[0])
			{
    			free(parser->cmd);
    			parser->cmd = ft_strdup(parser->arg[0]);
			}
			if (parser->cmd && parser->cmd[0] == '\0')
            {
				i = 0;
                if (parser->arg && parser->arg[1])
                {
                    i = 0;
                    free(parser->arg[0]);
                    while (parser->arg[i + 1])
                    {
                        parser->arg[i] = parser->arg[i + 1];
                        i++;
                    }
                    parser->arg[i] = NULL;
                    free(parser->cmd);
                    parser->cmd = ft_strdup(parser->arg[0]);
                }
                else
                {
                    shell->exit_status = 0;
                    free_token(imput, token);
                    free_parser(parser);
                    continue ;
                }
            }
			execute_cmd(parser, shell, token, imput);
		}
		free_token(imput, token);
		free_parser(parser);
	}
	free_shell(shell);
}
