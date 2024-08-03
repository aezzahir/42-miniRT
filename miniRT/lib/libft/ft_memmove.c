/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 09:24:22 by aezzahir          #+#    #+#             */
/*   Updated: 2023/11/15 20:11:02 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (n == 0 || dest == src)
		return (dest);
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		i = n - 1;
		while (i > 0)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i--;
		}
		((unsigned char *)dest)[0] = ((unsigned char *)src)[0];
	}
	return (dest);
}
