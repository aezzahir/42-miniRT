/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:24 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 11:27:00 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	mouse_release(int button, int x, int y, t_mlx_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->mouse.is_left_pressed = 0;
	if (button == 3)
		data->mouse.is_right_pressed = 0;
	return (0);
}

int	mouse_move(int x, int y, t_mlx_data *data)
{
	int			dx;
	int			dy;
	t_vector	translation;

	if (data && (data->mouse.is_left_pressed || data->mouse.is_right_pressed))
	{
		dx = x - data->mouse.last_x;
		dy = y - data->mouse.last_y;
		translation = get_world_space_translation(data, &data->scene->camera,
				dx, dy);
		if (data->mouse.is_left_pressed)
			transform_scene(data->scene, (t_vector){0, 0, 0}, translation,
				(t_color){0, 0, 0});
		data->redraw_needed = 1;
	}
	data->mouse.last_x = x;
	data->mouse.last_y = y;
	return (0);
}
