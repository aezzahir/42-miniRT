/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:15:49 by aezzahir          #+#    #+#             */
/*   Updated: 2023/11/13 21:23:54 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dlen;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	if (dstsize == 0 || dstsize <= ft_strlen(dst))
		return (slen + dstsize);
	j = ft_strlen(dst);
	dlen = j;
	while (i < dstsize - dlen - 1 && src[i])
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dlen + slen);
}
