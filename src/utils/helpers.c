
#include "../../include/miniRT.h"

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
		free(str);
	str = NULL;
}

void	handle_rotation(int key, t_vector *rotation, float rot_speed)
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

void	handle_translation(int key, t_vector *translation, float trans_speed)
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
