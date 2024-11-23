/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest_intersection1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:26:16 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 11:26:17 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

float	check_sphere_intersection(t_ray *ray, t_list *current,
		t_hit_info *nearest)
{
	t_sphere	*sphere;
	float		dist;

	sphere = (t_sphere *)(current->content);
	if (sphere->enable_intersection)
	{
		dist = get_sphere_distance(ray, sphere);
		if (dist < nearest->distance)
		{
			nearest->object = sphere;
			nearest->distance = dist;
			nearest->type = SPH;
		}
	}
	return (nearest->distance);
}

float	check_cylinder_intersection(t_ray *ray, t_list *current,
		t_hit_info *nearest)
{
	t_cylinder	*cylinder;
	float		dist;

	cylinder = (t_cylinder *)(current->content);
	if (cylinder->enable_intersection)
	{
		dist = get_cylinder_distance(ray, cylinder);
		if (dist < nearest->distance)
		{
			nearest->object = cylinder;
			nearest->distance = dist;
			nearest->type = CYL;
		}
	}
	return (nearest->distance);
}

float	check_plane_intersection(t_ray *ray, t_list *current,
		t_hit_info *nearest)
{
	t_plane	*plane;
	float	dist;

	plane = (t_plane *)(current->content);
	if (plane->enable_intersection)
	{
		dist = get_plane_distance(ray, plane);
		if (dist < nearest->distance)
		{
			nearest->object = plane;
			nearest->distance = dist;
			nearest->type = PLN;
		}
	}
	return (nearest->distance);
}

float	check_cone_intersection(t_ray *ray, t_list *current,
		t_hit_info *nearest)
{
	t_cone	*cone;
	float	dist;

	cone = (t_cone *)(current->content);
	if (cone->enable_intersection)
	{
		dist = get_cone_distance(ray, cone);
		if (dist < nearest->distance)
		{
			nearest->object = cone;
			nearest->distance = dist;
			nearest->type = CONE;
		}
	}
	return (nearest->distance);
}
