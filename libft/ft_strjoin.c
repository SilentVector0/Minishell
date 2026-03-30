/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathieu <mathieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:12:15 by mathieu           #+#    #+#             */
/*   Updated: 2025/10/07 19:11:53 by mathieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dest, const char *src1, const char *src2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src1[i])
	{
		dest[i] = src1[i];
		i ++;
	}
	while (src2[j])
	{
		dest[i + j] = src2[j];
		j++;
	}
	dest[i + j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final;
	size_t	i;

	i = ft_strlen(s1) + ft_strlen(s2);
	final = malloc((i + 1) * sizeof(char));
	if (!final)
		return (NULL);
	ft_strcpy(final, s1, s2);
	return (final);
}
