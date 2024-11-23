/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:59 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 05:23:12 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * plane.c
 * Implements plane intersection and normal calculations
 */
#include "../../include/miniRT.h"

t_plane	*create_plane(t_point point, t_vector normal, t_color color)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->point = point;
	plane->normal = vector_normalize(normal);
	plane->color = color;
	return (plane);
}

float	get_plane_distance(t_ray *ray, t_plane *plane)
{
	float		denom;
	t_vector	v;
	float		t;

	denom = vector_dot_product(plane->normal, ray->direction);
	if (fabs(denom) < 1e-6)
		return (INFINITY);
	v = vector_subtract(plane->point, ray->origin);
	t = vector_dot_product(v, plane->normal) / denom;
	if (t >= 0)
		return (t);
	return (INFINITY);
}
