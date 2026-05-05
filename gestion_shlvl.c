#include "minishell.h"

int verif_and_add(t_shell *shell, int i)
{
	int	j;
	int	value;
	char *new;
	char *temp;

	j = 6;
	printf("my shlvl: %s\n", shell->envp[i]);
	while (shell->envp[i][j])
	{
		if ((ft_isdigit(shell->envp[i][j]) == 0) || ft_atoi(shell->envp[i] + 6) < 0)
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strdup("SHLVL=0");
			return (0);
		}
		j++;
	}
	j = 6;
	value = ft_atoi(shell->envp[i] + j) + 1;
	printf("value: %d\n", value);
	temp = ft_itoa(value);
	new = ft_strjoin("SHLVL=", temp);
	free(shell->envp[i]);
	free (temp);
	shell->envp[i] = new;
	printf("%s\n", new);
	return (0);
}

void	increm_lvl(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "SHLVL=", 6) == 0)
			break ;
		i++;
	}
	printf("avant add\n");
	verif_and_add(shell, i);
	printf("apres add");
}