/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:10:41 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 15:51:15 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static int	fill_buffer(int fd, char *buffer,
	int *buffer_readed, int *buffer_pos)
{
	*buffer_readed = read(fd, buffer, 10);
	*buffer_pos = 0;
	return (*buffer_readed);
}

char	*get_next_line(int fd)
{
	static char	buffer[10];
	static int	buffer_readed = 0, buffer_pos = 0;
	char		line[70000];
	int			i;

	i = 0;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_readed
			&& fill_buffer(fd, buffer, &buffer_readed, &buffer_pos) <= 0)
			break ;
		line[i] = buffer[buffer_pos];
		buffer_pos++;
		if (line[i++] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}
