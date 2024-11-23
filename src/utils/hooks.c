/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:15 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 09:51:09 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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
