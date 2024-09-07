/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:34:30 by aezzahir          #+#    #+#             */
/*   Updated: 2023/11/16 18:32:29 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	size_t	i;
	void	*ptr;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	total_size = count * size;
	ptr = (void *)malloc(total_size);
	if (!ptr)
		return (NULL);
	if (ptr != NULL)
	{
		i = 0;
		while (i < total_size)
		{
			((char *)ptr)[i] = 0;
			i++;
		}
	}
	return (ptr);
}
