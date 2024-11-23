/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:15:56 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 11:16:06 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	camera_translate(t_camera *camera, t_vector translation)
{
	camera->position = vector_add(camera->position, translation);
}

void	ft_add_resize(float *d_h, float dx)
{
	if (*d_h + dx >= 0)
		*d_h += dx;
}
