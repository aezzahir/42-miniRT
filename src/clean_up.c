/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:25 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 22:23:04 by iben-haj         ###   ########.fr       */
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

void clear_object_list(t_list **object_list, void (*free_func)(void *))
{
    if (object_list && *object_list)
    {
        ft_lstclear(object_list, free_func);
        free(object_list);
        *object_list = NULL;
    }
}

void clear_scene(t_scene *scene)
{
    if (!scene)
        return;
    clear_object_list(scene->spheres, free_sphere);
    clear_object_list(scene->planes, free_plane);
    clear_object_list(scene->cylinders, free_cylinder);
    clear_object_list(scene->cones, free_cone);
    scene->camera = (t_camera){
        .position = {0, 0, 0},
        .orientation = {0, 0, 0},
        .fov = 0
    };
    scene->light = (t_light){
        .position = {0, 0, 0},
        .brightness = 0,
        .color = {0, 0, 0}
    };
    scene->ambient = (t_ambient){
        .ratio = 0,
        .color = {0, 0, 0}
    };
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
