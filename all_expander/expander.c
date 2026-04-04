#include "../minishell.h"

void	schr_in_env()
{
	
}

int	is_in_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] >= 'a' && str[i] <= 'z'\
		|| str[i] >= 'A' && str[i] <= 'Z'\
		|| str[i] == '_' || str[i] >= '0' && str[i] <= '9'))
		i++;
	return (i);
}

char	*search_var(char **arg, char **envp)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	while(arg[j])
	{
		while (arg[j][i])
		{
			if (arg[j][i] == '$')
			{
				i++;
				var = ft_substr(arg[j], i, is_in_var(arg[j] + i));
			}
			i++;
		}
		j++;
	}
}