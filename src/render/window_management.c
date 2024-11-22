/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:17 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 16:56:57 by iben-haj         ###   ########.fr       */
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



static void	handle_rotation(int key, t_vector *rotation, float rot_speed)
{
	if (key == 65362)
		rotation->x = rot_speed;
	else if (key == 65364)
		rotation->x = -rot_speed;
	else if (key == 65361)
		rotation->y = rot_speed;
	else if (key == 65363)
		rotation->y = -rot_speed;
	else if (key == 113)
		rotation->z = rot_speed;
	else if (key == 101)
		rotation->z = -rot_speed;
}

static void	handle_translation(int key, t_vector *translation, float trans_speed)
{
	if (key == 119)
		translation->z = trans_speed;
	else if (key == 115)
		translation->z = -trans_speed;
	else if (key == 97)
		translation->x = -trans_speed;
	else if (key == 100)
		translation->x = trans_speed;
	else if (key == 122)
		translation->y = trans_speed;
	else if (key == 120)
		translation->y = -trans_speed;
}

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
	float		rot_speed = 0.1;
	float		trans_speed = 0.5;
	float		d_h = 0;
	t_vector	rotation = {0, 0, 0};
	t_vector	translation = {0, 0, 0};
	t_color		color = {0, 0, 0};

	handle_rotation(key, &rotation, rot_speed);
	handle_translation(key, &translation, trans_speed);
	handle_color_and_resize(key, &color, &d_h);
	if (d_h != 0)
		ft_resize_unique_property(scene, 0, d_h);
	if (rotation.x || rotation.y || rotation.z || translation.x
		|| translation.y || translation.z || color.r || color.g || color.b)
		transform_scene(scene, rotation, translation, color);

	return (0);
}



t_vector get_object_position(t_object *object)
{
    if (object->type == SPH)
        return ((t_sphere *)object->shape)->center;
    else if (object->type == CYL)
        return ((t_cylinder *)object->shape)->center;
    else if (object->type == PLN)
        return ((t_plane *)object->shape)->point;
    else if (object->type == CONE)
        return ((t_cone *)object->shape)->center;
    
    return (t_vector){0, 0, 0};
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
