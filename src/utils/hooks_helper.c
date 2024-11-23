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
	float	d_r;

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
	t_ray			ray;
	t_intersection	*inter;

	ray = ft_generate_ray(x, y, data->scene);
	inter = ft_get_nearest_intersection(&ray, data->scene);
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