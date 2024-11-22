#include "../../include/miniRT.h"

int	mouse_hook(int button, int x, int y, t_mlx_data *data)
{
	float			d_r;
	t_ray			ray;
	t_intersection	*inter;

	d_r = 0;
	//
	if (button == 1)
		data->mouse.is_left_pressed = 1;
	if (button == 3)
		data->mouse.is_right_pressed = 1;
	if (button == 4 || button == 5)
	{
		if (button == 4)
			d_r = 0.5;
		else
			d_r = -0.5;
		ft_resize_unique_property(data->scene, d_r, 0);
	}
	data->mouse.last_x = x;
	data->mouse.last_y = y;
	if (button == 1)
	{
		ray = ft_generate_ray(x, y, data->scene);
		inter = ft_get_nearest_intersection(&ray, data->scene);
		if (inter)
		{
			(data->scene->selected_object).type = inter->object_type;
			(data->scene->selected_object).shape = inter->object;
			free(inter);
		}
	}
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
