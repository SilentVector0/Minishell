/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:29:27 by msuter            #+#    #+#             */
/*   Updated: 2025/10/09 15:26:02 by msuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

static size_t	mot(const char *chaine, char c)
{
	size_t	i;
	size_t	nbmot;

	i = 0;
	nbmot = 0;
	while (chaine[i])
	{
		while (chaine[i] == c)
			i++;
		if (!chaine[i])
			break ;
		nbmot++;
		while (chaine[i] && chaine[i] != c)
			i++;
	}
	return (nbmot);
}

static void	*free_all(char **final, size_t j)
{
	while (j > 0)
		free(final[--j]);
	free(final);
	return (NULL);
}

static int	assign(const char *s, char **final, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		len = i - start;
		final[j] = malloc(sizeof(char) * (len + 1));
		if (!final[j])
			return ((int)(size_t)free_all(final, j));
		ft_strlcpy(final[j], s + start, len + 1);
		j++;
	}
	final[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**final;
	size_t	nb_mot;

	if (!s)
		return (NULL);
	nb_mot = mot(s, c);
	final = malloc(sizeof(char *) * (nb_mot + 1));
	if (!final)
		return (NULL);
	if (!assign(s, final, c))
		return (NULL);
	return (final);
}
