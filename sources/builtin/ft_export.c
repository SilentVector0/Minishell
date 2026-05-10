#include "includes/minishell.h"


int	ft_export_display(t_shell *shell)
{
	int		i;
	char	*equal;

	i = 0;
	while (shell->envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		equal = ft_strchr(shell->envp[i], '=');
		if (equal)
		{
			write(1, shell->envp[i], equal - shell->envp[i] + 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(equal + 1, 1);
			ft_putstr_fd("\"", 1);
		}
		else
			ft_putstr_fd(shell->envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '=' || ((!ft_isalpha(str[i])) && str[i] != '_'))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_parser *parser, t_shell *shell)
{
	int		i;
	int		i_envp;
	int		ret;
	char	**tmp;

	if (!parser->arg[1])
		return (ft_export_display(shell));
	ret = 0;
	i = 0;
	while (parser->arg[++i])
	{
		ret = is_valid_identifier(parser->arg[i]);
		if (ret)
			continue ;
		i_envp = find_env(shell->envp, parser->arg[i]);
		tmp = change_var(shell->envp, parser->arg[i], i_envp);
		if (!tmp)
			return (1);
		shell->envp = tmp;
	}
	return (ret);
}
