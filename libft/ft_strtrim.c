/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 02:20:31 by mathieu           #+#    #+#             */
/*   Updated: 2025/10/13 15:26:28 by msuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	count_fin(const char *s1, const char *set, int *fin, int *debut)
{
	size_t	i;
	int		j;

	i = 0;
	j = ft_strlen(s1);
	while (set[i])
	{
		if (j > *debut && set[i] == s1[j - 1])
		{
			i = 0;
			j--;
			(*fin)--;
			continue ;
		}
		i++;
	}
}

static void	count_debut(const char *s1, const char *set, int	*debut)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (set[i])
	{
		if (set[i] == s1[j] && s1[j] != '\0')
		{
			i = 0;
			j++;
			(*debut)++;
			continue ;
		}
		i++;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*final;
	int		debut;
	int		fin;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	debut = 0;
	fin = ft_strlen(s1);
	count_debut(s1, set, &debut);
	count_fin(s1, set, &fin, &debut);
	if (fin > debut)
		j = fin - debut;
	else
		j = 0;
	final = malloc((j + 1) * sizeof(char));
	if (!final)
		return (NULL);
	ft_memcpy(final, s1 + debut, j);
	final[j] = '\0';
	return (final);
}
