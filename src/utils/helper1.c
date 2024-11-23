#include "../../include/miniRT.h"

void	camera_translate(t_camera *camera, t_vector translation)
{
	camera->position = vector_add(camera->position, translation);
}

void	ft_add_resize(float *d_h, float dx)
{
	if (*d_h + dx >= 0)
		*d_h += dx;
}