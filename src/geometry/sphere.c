/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:12:47 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 05:23:23 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file sphere.c
 * @brief Implements sphere intersection calculations
 */

#include "../../include/miniRT.h"

float	get_sphere_distance(t_ray *ray, t_sphere *sphere)
{
	t_vector	oc;

	float(a), (b), (c), (discriminant), (t1), (t2);
	oc = vector_subtract(ray->origin, sphere->center);
	a = vector_dot_product(ray->direction, ray->direction);
	b = 2.0 * vector_dot_product(oc, ray->direction);
	c = vector_dot_product(oc, oc) - (sphere->diameter * sphere->diameter
			/ 4.0);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (INFINITY);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 0)
		return (t1);
	if (t2 > 0)
		return (t2);
	return (INFINITY);
}
