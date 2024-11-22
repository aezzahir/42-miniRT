/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:15 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 17:23:29 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	handle_button_presses(int button, t_mlx_data *data)
{
	if (button == 1)
		data->mouse.is_left_pressed = 1;
	else if (button == 3)
		data->mouse.is_right_pressed = 1;
}

void	handle_zoom(int button, t_mlx_data *data)
{
	float d_r;

	d_r = 0;	
	if (button == 4)
	{
		d_r = 0.5;
	}
	else if (button == 5)
	{
		d_r = -0.5;
	}
	ft_resize_unique_property(data->scene, d_r, 0);
}

void	update_mouse_position(int x, int y, t_mlx_data *data)
{
	data->mouse.last_x = x;
	data->mouse.last_y = y;
}

void	handle_object_selection(int x, int y, t_mlx_data *data)
{
	t_ray ray = ft_generate_ray(x, y, data->scene);
	t_intersection *inter = ft_get_nearest_intersection(&ray, data->scene);
	if (inter)
	{
		data->scene->selected_object.type = inter->object_type;
		data->scene->selected_object.shape = inter->object;
		free(inter); // Free only if intersection is found
	}
}

int	mouse_hook(int button, int x, int y, t_mlx_data *data)
{
	handle_button_presses(button, data);
	if (button == 4 || button == 5)
		handle_zoom(button, data);
	update_mouse_position(x, y, data);
	if (button == 1)
		handle_object_selection(x, y, data);
	data->redraw_needed = 1;

	return (0);
}


int	key_hook(int keycode, t_mlx_data *data)
{
	if (keycode == 65307)
		ft_close(data);
	if (keycode == 'c')
		data->scene->selected_object.type = CAM;
	if (keycode == 'l')
	{
		data->scene->selected_object.type = LIGHT;
		data->scene->selected_object.shape = &(data->scene->light);
		vector_print(data->scene->light.position);
	}
	if (keycode == 'r')
		data->redraw_needed = 1;
	handle_user_input(keycode, data->scene);
	data->redraw_needed = 1;
	return (0);
}

int	expose_hook(t_mlx_data *data)
{
	data->redraw_needed = 1;
	return (0);
}

int	loop_hook(t_mlx_data *data)
{
	if (data->redraw_needed)
	{
		render_scene(data->scene, data);
		mlx_put_image_to_window(data->mlx_connection, data->mlx_window,
			data->image.img_ptr, 0, 0);
		data->redraw_needed = 0;
	}
	return (0);
}

int	ft_close(t_mlx_data *data)
{
	if (data->mlx_connection)
	{
		if (data->image.img_ptr)
			mlx_destroy_image(data->mlx_connection, data->image.img_ptr);
		if (data->mlx_window)
			mlx_destroy_window(data->mlx_connection, data->mlx_window);
		mlx_destroy_display(data->mlx_connection);
		free(data->mlx_connection);
	}
	clear_scene(data->scene);
	exit(0);
	return (0);
}
