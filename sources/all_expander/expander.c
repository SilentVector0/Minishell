/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 11:42:29 by aroduit           #+#    #+#             */
/*   Updated: 2026/06/07 11:49:56 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	replace(t_parser *parser, char *tmp, int j, int len)
{
	char	*res;
	int		i;
	int		k;
	int		new_len;

	new_len = ft_strlen(parser->arg[j]) - len - 1 + ft_strlen(tmp);
	if (new_len < 0)
		new_len = 0;
	res = malloc(sizeof(char) * (new_len + 1));
	if (!res)
		return ;
	i = 0;
	k = 0;
	while (parser->arg[j][i] && parser->arg[j][i] != '$')
		res[k++] = parser->arg[j][i++];
	i += len + 1;
	while (*tmp)
		res[k++] = *tmp++;
	while (parser->arg[j][i])
		res[k++] = parser->arg[j][i++];
	res[k] = '\0';
	free(parser->arg[j]);
	parser->arg[j] = res;
}

char	*schr_in_env(char *var, char **envp)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen(var);
	i = 0;
	if (envp == NULL || len == 1)
	{
		res = special_case(envp, len);
		return (res);
	}
	while (envp[i])
	{
		if (strncmp(var, envp[i], len) == 0)
		{
			res = ft_substr(envp[i], len, ft_strlen(envp[i]) - len);
			return (res);
		}
		i++;
	}
	res = malloc (sizeof(char) * 1);
	res[0] = '\0';
	return (res);
}

int	count_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] == '_') || (str[i] >= '0' && str[i] <= '9')))
		i++;
	return (i);
}

void	special_var(t_parser *parser, int j, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		i;
	int		new_size;
	int		k;

	i = 0;
	k = 0;
	tmp = ft_itoa(shell->exit_status);
	new_size = ft_strlen(tmp) + ft_strlen(parser->arg[j]) - 2;
	new = malloc(sizeof(char) * new_size + 1);
	while (parser->arg[j][i])
	{
		if (case_interrog(parser, &new_size, &i, &j) == 1)
		{
			ft_memcpy(new + k, tmp, ft_strlen(tmp));
			k += ft_strlen(tmp);
		}
		else
			new[k++] = parser->arg[j][i++];
	}
	new[k] = '\0';
	free (parser->arg[j]);
	free(tmp);
	parser->arg[j] = new;
}

void    split_arg(t_parser *parser, int j)
{
    char    **split;
    char    **new_arg;
    int     old_len;
    int     split_len;
    int     i;
    int     k;

    split = ft_split(parser->arg[j], ' ');
    split_len = 0;
    while (split[split_len])
        split_len++;
    old_len = 0;
    while (parser->arg[old_len])
        old_len++;
    new_arg = malloc(sizeof(char *) * (old_len + split_len));
    k = 0;
    i = 0;
    while (i < j)
        new_arg[k++] = parser->arg[i++];
    i = 0;
    while (split[i])
        new_arg[k++] = split[i++];
    free(split);
    i = j + 1;
    while (parser->arg[i])
        new_arg[k++] = parser->arg[i++];
    new_arg[k] = NULL;
    free(parser->arg[j]);
    free(parser->arg);
    parser->arg = new_arg;
}

void	search_var(t_parser *parser, t_shell *shell)
{
	t_var	var;

	var.j = 0;
	if (parser->arg)
	{
		while (parser->arg[var.j])
		{
			init_var (&var);
			while (parser->arg[var.j][var.i])
			{
				if (verif_and_schr_in_env(parser, &var, shell) == 1)
					break ;
			}
			if (var.tmp != NULL)
			{
				replace(parser, var.tmp, var.j, var.len);
				free(var.tmp);
				var.tmp = NULL;
				if (ft_strchr(parser->arg[var.j], ' '))
        			split_arg(parser, var.j);
				continue ;
			}
			if (parser->arg[var.j][var.i] == '\0')
				free_my_var(parser, &var);
		}
	}
}
