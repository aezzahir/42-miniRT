/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:20:51 by aezzahir          #+#    #+#             */
/*   Updated: 2023/11/04 09:32:42 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	unsigned char	value;
	size_t			i;

	p = b;
	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		p[i] = value;
		i++;
	}
	return (b);
}
