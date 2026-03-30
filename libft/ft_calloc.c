/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:25:51 by mathieu           #+#    #+#             */
/*   Updated: 2025/10/08 14:02:52 by msuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;
	size_t	i;

	i = 0;
	if (size && count > (size_t)-1 / size)
		return (NULL);
	tab = malloc(count * size);
	if (!tab)
		return (NULL);
	while (i < count * size)
	{
		((unsigned char *)tab)[i] = 0;
		i++;
	}
	return (tab);
}
