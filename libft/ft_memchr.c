/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathieu <mathieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:43:09 by mathieu           #+#    #+#             */
/*   Updated: 2025/10/02 14:44:46 by mathieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	a;
	size_t			i;

	i = 0;
	a = (unsigned char)c;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (((unsigned char *)s)[i] == a)
		{
			return ((void *)(unsigned char *)s + i);
		}
		i++;
	}
	return (NULL);
}
