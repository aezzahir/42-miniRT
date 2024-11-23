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

t_vector	get_perpendicular_vector(t_vector v, t_vector x)
{
	return (vector_subtract(v, vector_multiply(x, vector_dot_product(v, x))));
}

float	calculate_discriminant(t_vector v, t_vector oc_perp, float radius)
{
	float	a;
	float	b;
	float	c;

	a = vector_dot_product(v, v);
	b = 2 * vector_dot_product(v, oc_perp);
	c = vector_dot_product(oc_perp, oc_perp) - radius * radius;
	return (b * b - 4 * a * c);
}

float	solve_quadratic(float a, float b, float discriminant)
{
	float		t_body1;
	float		t_body2;

	t_body1 = (-b - sqrt(discriminant)) / (2 * a);
	t_body2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t_body1 >= 0)
		return (t_body1);
	return (t_body2);
}

bool	is_within_body(t_point body_hit, t_cylinder *cyl)
{
	float		body_height;

	body_height = vector_dot_product(vector_subtract(
				body_hit, cyl->center), cyl->axis);
	return (body_height >= 0 && body_height <= cyl->height);
}

float	get_bottom_cap_distance(t_ray *ray, t_cylinder *cyl, float denom)
{
	float	t;
	t_point	hit;

	if (fabs(denom) > 1e-6)
	{
		t = vector_dot_product(
				vector_subtract(cyl->center, ray->origin), cyl->axis) / denom;
		if (t >= 0)
		{
			hit = vector_add(ray->origin, vector_multiply(ray->direction, t));
			if (vector_distance(hit, cyl->center) <= cyl->diameter / 2)
				return (t);
		}
	}
	return (INFINITY);
}
