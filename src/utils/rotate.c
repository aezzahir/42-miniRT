/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:00:40 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 11:17:38 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static void	apply_rotation(t_vector *axis, t_vector r)
{
	*axis = rotate_x(*axis, r.x);
	*axis = rotate_y(*axis, r.y);
	*axis = rotate_z(*axis, r.z);
}

void	object_rotate(t_object *o, t_vector r)
{
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;

	if (o->type == PLN)
	{
		plane = (t_plane *)o->shape;
		apply_rotation(&plane->normal, r);
	}
	else if (o->type == CYL)
	{
		cylinder = (t_cylinder *)o->shape;
		apply_rotation(&cylinder->axis, r);
	}
	else if (o->type == CONE)
	{
		cone = (t_cone *)o->shape;
		apply_rotation(&cone->axis, r);
	}
}

void	camera_rotate(t_camera *camera, t_vector rotation)
{
	camera->orientation = rotate_x(camera->orientation, rotation.x);
	camera->orientation = rotate_y(camera->orientation, rotation.y);
	camera->orientation = rotate_z(camera->orientation, rotation.z);
	camera->up = rotate_x(camera->up, rotation.x);
	camera->up = rotate_y(camera->up, rotation.y);
	camera->up = rotate_z(camera->up, rotation.z);
	camera->right = vector_cross_product(camera->orientation, camera->up);
	camera->up = vector_cross_product(camera->right, camera->orientation);
}
