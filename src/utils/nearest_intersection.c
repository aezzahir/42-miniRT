/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:27 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 09:36:31 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	check_spheres(t_ray *ray, t_scene *scene, t_hit_info *nearest)
{
	t_list	*current;

	current = *(scene->spheres);
	while (current)
	{
		check_sphere_intersection(ray, current, nearest);
		current = current->next;
	}
}

void	check_cylinders(t_ray *ray, t_scene *scene, t_hit_info *nearest)
{
	t_list	*current;

	current = *(scene->cylinders);
	while (current)
	{
		check_cylinder_intersection(ray, current, nearest);
		current = current->next;
	}
}

void	check_planes(t_ray *ray, t_scene *scene, t_hit_info *nearest)
{
	t_list	*current;

	current = *(scene->planes);
	while (current)
	{
		check_plane_intersection(ray, current, nearest);
		current = current->next;
	}
}

void	check_cones(t_ray *ray, t_scene *scene, t_hit_info *nearest)
{
	t_list	*current;

	current = *(scene->cones);
	while (current)
	{
		check_cone_intersection(ray, current, nearest);
		current = current->next;
	}
}

t_intersection	*ft_get_nearest_intersection(t_ray *ray, t_scene *scene)
{
	t_hit_info	nearest;

	nearest = {NULL, INFINITY, NONE};
	check_spheres(ray, scene, &nearest);
	check_cylinders(ray, scene, &nearest);
	check_planes(ray, scene, &nearest);
	check_cones(ray, scene, &nearest);
	if (nearest.distance == INFINITY)
		return (NULL);
	return (create_intersection(ray, &nearest));
}
