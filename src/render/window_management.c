/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:17 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 09:39:33 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(img->img_pixel_ptr + offset)) = color;
}

int	key_press(int keycode, t_mlx_data *data)
{
	handle_user_input(keycode, data->scene);
	return (0);
}

int	handle_user_input(int key, t_scene *scene)
{
	t_vector	rotation;
	t_vector	translation;
	t_color		color;
	float		rot_speed;
	float		trans_speed;
	float		d_h;

	rotation = {0, 0, 0};
	translation = {0, 0, 0};
	color = {0, 0, 0};
	rot_speed = 0.1;
	trans_speed = 0.5;
	d_h = 0;
	if (key == 65362)
		rotation.x = rot_speed;
	else if (key == 65364) /
		rotation.x = -rot_speed;
	else if (key == 65361)
		rotation.y = rot_speed;
	else if (key == 65363)
		rotation.y = -rot_speed;
	else if (key == 113)
		rotation.z = rot_speed;
	else if (key == 101)
		rotation.z = -rot_speed;

    // Translation
	else if (key == 119)
		translation.z = trans_speed;
	else if (key == 115)
		translation.z = -trans_speed;
	else if (key == 97)
		translation.x = -trans_speed;
	else if (key == 100)
		translation.x = trans_speed;
	else if (key == 122)
		translation.y = trans_speed;
	else if (key == 120)
		translation.y = -trans_speed;
	else if (key == 'r')
		color.r++;
	else if (key == 'g')
		color.g++;
	else if (key == 'b')
		color.b++;
	else if (key == 61)
		d_h = 0.5;
	else if (key == '-')
		d_h = -0.5;
	if (d_h != 0)
		ft_resize_unique_property(scene, 0, d_h);
	if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0
		|| translation.x != 0 || translation.y != 0 || translation.z != 0
		|| color.r || color.g || color.b)
	{
		transform_scene(scene, rotation, translation, color);
	}
	return (0);
}

t_vector	get_object_position(t_object *object)
{
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;
	t_cone		*cone;

	if (object->type == SPH)
	{
		sphere = (t_sphere *)object->shape;
		return (sphere->center);
	}
	else if (object->type == CYL)
	{
		cylinder = (t_cylinder *)object->shape;
		return (cylinder->center);
	}
	else if (object->type == PLN)
	{
		plane = (t_plane *)object->shape;
		return (plane->point);
	}
	else if (object->type == CONE)
	{
		cone = (t_cone *)object->shape;
		return (cone->center);
	}
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
