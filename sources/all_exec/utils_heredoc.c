/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 21:39:42 by msuter            #+#    #+#             */
/*   Updated: 2026/06/06 22:53:51 by msuter           ###   ########.fr       */
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
	tmp = malloc(sizeof(char) * count + 1);
	j = 0;
	while (j != count)
	{
		tmp[j] = (*str)[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	var = schr_in_env(tmp, shell->envp);
	free(tmp);
	new_str(str, var, count);
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