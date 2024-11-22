/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:25 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 09:56:15 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// Main scene cleanup function
void	clear_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->spheres)
	{
		ft_lstclear(scene->spheres, free_sphere);
		free(scene->spheres);
		scene->spheres = NULL;
	}
	if (scene->planes)
	{
		ft_lstclear(scene->planes, free_plane);
		free(scene->planes);
		scene->planes = NULL;
	}
	if (scene->cylinders)
	{
		ft_lstclear(scene->cylinders, free_cylinder);
		free(scene->cylinders);
		scene->cylinders = NULL;
	}
	if (scene->cones)
	{
		ft_lstclear(scene->cones, free_cone);
		free(scene->cones);
		scene->cones = NULL;
	}
	scene->camera.position = (t_vector){0, 0, 0};
	scene->camera.orientation = (t_vector){0, 0, 0};
	scene->camera.fov = 0;
	scene->light.position = (t_vector){0, 0, 0};
	scene->light.brightness = 0;
	scene->light.color = (t_color){0, 0, 0};
	scene->ambient.ratio = 0;
	scene->ambient.color = (t_color){0, 0, 0};
}

void	reset_scene(t_scene *scene)
{
	clear_scene(scene);
	scene->spheres = malloc(sizeof(t_list *));
	scene->planes = malloc(sizeof(t_list *));
	scene->cylinders = malloc(sizeof(t_list *));
	scene->cones = malloc(sizeof(t_list *));
	if (scene->spheres)
		*(scene->spheres) = NULL;
	if (scene->planes)
		*(scene->planes) = NULL;
	if (scene->cylinders)
		*(scene->cylinders) = NULL;
	if (scene->cones)
		*(scene->cones) = NULL;
	scene->camera.position = (t_vector){0, 0, 0};
	scene->camera.orientation = (t_vector){0, 0, 1};
	scene->camera.fov = 60;
	scene->light.position = (t_vector){0, 0, 0};
	scene->light.brightness = 1.0;
	scene->light.color = (t_color){255, 255, 255};
	scene->ambient.ratio = 0.1;
	scene->ambient.color = (t_color){255, 255, 255};
}

bool	init_scene(t_scene *scene)
{
	scene->spheres = malloc(sizeof(t_list *));
	if (!scene->spheres)
		return (false);
	scene->planes = malloc(sizeof(t_list *));
	if (!scene->planes)
	{
		free(scene->spheres);
		return (false);
	}
	scene->cylinders = malloc(sizeof(t_list *));
	if (!scene->cylinders)
	{
		free(scene->spheres);
		free(scene->planes);
		return (false);
	}
	scene->cones = malloc(sizeof(t_list *));
	if (!scene->cones)
	{
		free(scene->spheres);
		free(scene->planes);
		free(scene->cylinders);
		return (false);
	}
	*(scene->spheres) = NULL;
	*(scene->planes) = NULL;
	*(scene->cylinders) = NULL;
	*(scene->cones) = NULL;
	return (true);
}
