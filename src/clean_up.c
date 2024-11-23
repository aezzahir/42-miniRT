/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:25 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 10:05:10 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	clear_scene(t_scene *scene)
{
	if (!scene)
		return ;
	clear_object_list(scene->spheres, free_sphere);
	clear_object_list(scene->planes, free_plane);
	clear_object_list(scene->cylinders, free_cylinder);
	clear_object_list(scene->cones, free_cone);
	scene->camera = (t_camera){.position = {0, 0, 0}, .orientation = {0, 0, 0},
		.fov = 0};
	scene->light = (t_light){.position = {0, 0, 0}, .brightness = 0,
		.color = {0, 0, 0}};
	scene->ambient = (t_ambient){.ratio = 0, .color = {0, 0, 0}};
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

void	ft_free_shape(t_scene *scene)
{
	free(scene->spheres);
	free(scene->planes);
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
		ft_free_shape(scene);
		return (false);
	}
	scene->cones = malloc(sizeof(t_list *));
	if (!scene->cones)
	{
		ft_free_shape(scene);
		free(scene->cylinders);
		return (false);
	}
	*(scene->spheres) = NULL;
	*(scene->planes) = NULL;
	*(scene->cylinders) = NULL;
	*(scene->cones) = NULL;
	return (true);
}
