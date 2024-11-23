/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:17 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 10:14:51 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static void	handle_color_and_resize(int key, t_color *color, float *d_h)
{
	if (key == 'r')
		color->r++;
	else if (key == 'g')
		color->g++;
	else if (key == 'b')
		color->b++;
	else if (key == 61)
		*d_h = 0.5;
	else if (key == '-')
		*d_h = -0.5;
}

int	handle_user_input(int key, t_scene *scene)
{
	const float	rot_speed = 0.1;
	const float	trans_speed = 0.5;
	t_vector	rotation;
	t_vector	translation;
	t_color		color;
	float		d_h;

	rotation = vector_create(0, 0, 0);
	translation = vector_create(0, 0, 0);
	color.r = 0;
	color.g = 0;
	color.b = 0;
	d_h = 0;
	handle_rotation(key, &rotation, rot_speed);
	handle_translation(key, &translation, trans_speed);
	handle_color_and_resize(key, &color, &d_h);
	if (d_h != 0)
		ft_resize_unique_property(scene, 0, d_h);
	if (rotation.x || rotation.y || rotation.z || translation.x || translation.y
		|| translation.z || color.r || color.g || color.b)
		transform_scene(scene, rotation, translation, color);
	return (0);
}

t_vector	get_object_position(t_object *object)
{
	if (object->type == SPH)
		return (((t_sphere *)object->shape)->center);
	else if (object->type == CYL)
		return (((t_cylinder *)object->shape)->center);
	else if (object->type == PLN)
		return (((t_plane *)object->shape)->point);
	else if (object->type == CONE)
		return (((t_cone *)object->shape)->center);
	return ((t_vector){0, 0, 0});
}

t_vector	get_world_space_translation(t_mlx_data *data, t_camera *camera,
		int dx, int dy)
{
	float		world_dx;
	t_vector	translation;
	float		distance_scale;
	t_vector	obj_pos;
	float		dist;
	float		world_dy;

	world_dx = (dx * camera->viewport_width) / WIDTH;
	world_dy = -(dy * camera->viewport_height) / HEIGHT;
	translation = vector_add(vector_multiply(camera->right, world_dx),
			vector_multiply(camera->up, world_dy));
	distance_scale = 1.0f;
	if (data->scene->selected_object.type != NONE)
	{
		obj_pos = get_object_position(&data->scene->selected_object);
		dist = fabsf(vector_dot_product(vector_subtract(obj_pos,
						camera->position), camera->forward));
		distance_scale = dist;
	}
	return (vector_multiply(translation, distance_scale));
}
