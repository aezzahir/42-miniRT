/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:51:37 by aezzahir          #+#    #+#             */
/*   Updated: 2023/11/15 18:16:11 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	while (i < len && str[i] != '\0')
	{
		while (str[i + j] == to_find[j] && str[i + j] != '\0' && (i + j) < len)
			j++;
		if (to_find[j] == '\0')
			return ((char *)(str + i));
		i++;
		j = 0;
	}
	return (NULL);
}
