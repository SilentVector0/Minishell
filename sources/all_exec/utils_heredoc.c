/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 11:58:19 by aroduit           #+#    #+#             */
/*   Updated: 2026/06/07 11:58:34 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	new_str(char **str, char *tmp, int len)
{
	char	*res;
	int		i;
	int		k;
	int		l;

	init_replace(&i, &k, &l);
	i = ft_strlen(*str) + ft_strlen(tmp) - len;
	res = malloc(sizeof(char) * i + 1);
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			i += len + 1;
			while (tmp[l])
				res[k++] = tmp[l++];
			while ((*str)[i])
				res[k++] = (*str)[i++];
			break ;
		}
		res[k++] = (*str)[i++];
	}
	res[k] = '\0';
	free(*str);
	*str = res;
}

static int	replace_var(char **str, int i, t_shell *shell)
{
	char *tmp;
	char *var;
	int	count;
	int	j;

	j = i;
	count = 0;
	while (ft_isalpha((*str)[j]) || (*str)[j] == '_')
	{
		count++;
		j++;
	}
	tmp = malloc(sizeof(char) * (count + 1));
	j = 0;
	while (j != count)
	{
		tmp[j] = (*str)[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	var = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = schr_in_env(var, shell->envp);
	free(var);
	new_str(str, tmp, count);
	free(tmp);
	return (count);
}

void	expand_heredoc(char **str, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			j = replace_var(str, i + 1, shell);
			i += j;
			continue ;
		}
		i++;
	}
}