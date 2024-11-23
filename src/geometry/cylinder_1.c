/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:54 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 09:29:21 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * cylinder.c
 * Implements cylinder intersection and normal calculations
 */

#include "../../include/miniRT.h"

float	get_top_cap_distance(t_ray *ray, t_cylinder *cyl, float d)
{
	t_point	c;
	t_point	hit;
	float	t;

	c = vector_add(cyl->center, vector_multiply(cyl->axis, cyl->height));
	if (fabs(d) > 1e-6)
	{
		t = vector_dot_product(vector_subtract(c, ray->origin), cyl->axis) / d;
		if (t >= 0)
		{
			hit = vector_add(ray->origin, vector_multiply(ray->direction, t));
			if (vector_distance(hit, c) <= cyl->diameter / 2)
				return (t);
		}
	}
	return (INFINITY);
}

float	compute_cap_distance(t_ray *ray, t_cylinder *cyl)
{
	float	denom;
	float	t_bottom;

	denom = vector_dot_product(ray->direction, cyl->axis);
	t_bottom = get_bottom_cap_distance(ray, cyl, denom);
	if (t_bottom < INFINITY)
		return (t_bottom);
	return (get_top_cap_distance(ray, cyl, denom));
}

float	compute_body_distance(t_ray *ray, t_cylinder *cyl)
{
	t_vector	oc;
	t_vector	v;
	t_point		hit;

	float (a), (b), (t_body), (discriminant);
	oc = vector_subtract(ray->origin, cyl->center);
	v = get_perpendicular_vector(ray->direction, cyl->axis);
	oc = get_perpendicular_vector(oc, cyl->axis);
	discriminant = calculate_discriminant(v, oc, cyl->diameter / 2);
	if (discriminant < 0)
		return (-1);
	a = vector_dot_product(v, v);
	b = 2 * vector_dot_product(v, oc);
	t_body = solve_quadratic(a, b, discriminant);
	if (t_body >= 0)
	{
		hit = vector_add(ray->origin, vector_multiply(ray->direction, t_body));
		if (is_within_body(hit, cyl))
			return (t_body);
	}
	return (-1);
}

float	get_cylinder_distance(t_ray *ray, t_cylinder *cyl)
{
	float	t_body;

	t_body = compute_body_distance(ray, cyl);
	if (t_body >= 0)
		return (t_body);
	return (compute_cap_distance(ray, cyl));
}

t_vector	calculate_cylinder_normal(t_cylinder *cyl, t_point hit_point)
{
	t_vector	cp;
	float		projection_length;
	t_vector	projection;
	t_vector	normal;

	cp = vector_subtract(hit_point, cyl->center);
	projection_length = vector_dot_product(cp, cyl->axis);
	if (projection_length <= 0)
		return (vector_negate(cyl->axis));
	if (projection_length >= cyl->height)
		return (cyl->axis);
	projection = vector_multiply(cyl->axis, projection_length);
	normal = vector_subtract(cp, projection);
	return (vector_normalize(normal));
}
