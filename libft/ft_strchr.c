/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:52:13 by msuter            #+#    #+#             */
/*   Updated: 2025/10/13 16:24:39 by msuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;
	size_t			i;

	i = 0;
	ch = (unsigned char)c;
	while (1)
	{
		if ((unsigned char)s[i] == ch)
			return ((char *)s + i);
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (NULL);
}
