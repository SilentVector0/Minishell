/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathieu <mathieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:19:17 by msuter            #+#    #+#             */
/*   Updated: 2025/10/07 17:19:37 by mathieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && size > 1)
	{
		dest[i] = src[i];
		i++;
		size--;
	}
	if (size != 0)
		dest[i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i);
}
