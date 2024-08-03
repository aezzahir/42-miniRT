/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:16:29 by aezzahir          #+#    #+#             */
/*   Updated: 2023/11/05 18:41:31 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	max_to_copy;

	if (dstsize == 0)
		return (ft_strlen(src));
	else
		max_to_copy = dstsize - 1;
	i = 0;
	while (src[i] != '\0' && i < max_to_copy)
	{
		dst[i] = src [i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
