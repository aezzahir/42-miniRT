/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:17 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 11:50:34 by benhajdahma      ###   ########.fr       */
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
	t_transform	transform;

	transform.rotation = vector_create(0, 0, 0);
	transform.translation = vector_create(0, 0, 0);
	transform.color.r = 0;
	transform.color.g = 0;
	transform.color.b = 0;
	transform.d_h = 0;
	handle_rotation(key, &transform.rotation, 0.1);
	handle_translation(key, &transform.translation, 0.5);
	handle_color_and_resize(key, &transform.color, &transform.d_h);
	if (transform.d_h != 0)
		ft_resize_unique_property(scene, 0, transform.d_h);
	if (transform.rotation.x || transform.rotation.y || transform.rotation.z
		|| transform.translation.x || transform.translation.y
		|| transform.translation.z || transform.color.r || transform.color.g
		|| transform.color.b)
		transform_scene(scene, transform.rotation, transform.translation,
			transform.color);
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
	translation = vector_add(vector_multiply(camera->forward, world_dx),
			vector_multiply(camera->up, world_dy));
	distance_scale = 1.0f;
	if (data->scene->selected_object.type != NONE)
	{
		wt.obj_pos = get_object_position(&data->scene->selected_object);
		wt.dist = fabsf(vector_dot_product(vector_subtract(wt.obj_pos,
						camera->position), camera->forward));
		wt.distance_scale = wt.dist;
	}
	return (vector_multiply(wt.translation, wt.distance_scale));
}
