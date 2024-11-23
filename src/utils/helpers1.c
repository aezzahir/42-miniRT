/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:15:56 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 12:04:02 by iben-haj         ###   ########.fr       */
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

t_vector	get_normal(void *object, t_vector point, int type)
{
	if (type == SPH)
		return (vector_normalize(vector_subtract(point,
					((t_sphere *)object)->center)));
	if (type == CYL)
		return (calculate_cylinder_normal(object, point));
	if (type == PLN)
		return (((t_plane *)object)->normal);
	if (type == CONE)
		return (calculate_cone_normal(object, point));
	return ((t_vector){0, 0, 0});
}
