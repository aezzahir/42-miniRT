#include "../include/miniRT.h"

void	free_sphere(void *content)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)content;
	if (sphere)
		free(sphere);
}

void	free_plane(void *content)
{
	t_plane	*plane;

	plane = (t_plane *)content;
	if (plane)
		free(plane);
}

void	free_cylinder(void *content)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)content;
	if (cylinder)
		free(cylinder);
}

void	free_cone(void *content)
{
	t_cone	*cone;

	cone = (t_cone *)content;
	if (cone)
		free(cone);
}

void	clear_object_list(t_list **object_list, void (*free_func)(void *))
{
	if (object_list && *object_list)
	{
		ft_lstclear(object_list, free_func);
		free(object_list);
		*object_list = NULL;
	}
}