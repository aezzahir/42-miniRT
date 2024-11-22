/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:54 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 09:35:06 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * cylinder.c
 * Implements cylinder intersection and normal calculations
 */

#include "../../include/miniRT.h"

t_cylinder	*create_cylinder(t_point center, t_vector axis, float diameter,
		float height, t_color color)
{
	t_cylinder	*cylinder;

	cylinder = NULL;
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
	{
		printf("malloc error in create_cylinder\n");
		return (NULL);
	}
	cylinder->center = center;
	cylinder->axis = vector_normalize(axis);
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->color = color;
	return (cylinder);
}

float	get_cylinder_distance(t_ray *ray, t_cylinder *cyl)
{
	t_vector	oc;
	float		radius;
	t_vector	v_dir_perpendicular;
	t_vector	oc_perpendicular;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t_body1;
	float		t_body2;
	float		t_body;
	t_point		body_hit;
	float		body_height;
	float		t_cap;
	float		denom;
	float		t;
	t_point		hit;
	t_point		top_center;
	float		t;
	t_point		hit;

	oc = vector_subtract(ray->origin, cyl->center);
	radius = cyl->diameter / 2;
	v_dir_perpendicular = vector_subtract(ray->direction,
			vector_multiply(cyl->axis, vector_dot_product(ray->direction,
					cyl->axis)));
	oc_perpendicular = vector_subtract(oc, vector_multiply(cyl->axis,
				vector_dot_product(oc, cyl->axis)));
	a = vector_dot_product(v_dir_perpendicular, v_dir_perpendicular);
	b = 2 * vector_dot_product(v_dir_perpendicular, oc_perpendicular);
	c = vector_dot_product(oc_perpendicular, oc_perpendicular) - radius
		* radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (INFINITY);
	t_body1 = (-b - sqrt(discriminant)) / (2 * a);
	t_body2 = (-b + sqrt(discriminant)) / (2 * a);
	t_body = (t_body1 >= 0) ? t_body1 : t_body2;
	if (t_body >= 0)
	{
		body_hit = vector_add(ray->origin, vector_multiply(ray->direction,
					t_body));
		body_height = vector_dot_product(vector_subtract(body_hit, cyl->center),
				cyl->axis);
		if (body_height >= 0 && body_height <= cyl->height)
			return (t_body);
	}
	t_cap = INFINITY;
	denom = vector_dot_product(ray->direction, cyl->axis);
	if (fabs(denom) > 1e-6)
	{
		t = vector_dot_product(vector_subtract(cyl->center, ray->origin),
				cyl->axis) / denom;
		if (t >= 0)
		{
			hit = vector_add(ray->origin, vector_multiply(ray->direction, t));
			if (vector_distance(hit, cyl->center) <= radius)
				t_cap = t;
		}
	}
	top_center = vector_add(cyl->center, vector_multiply(cyl->axis,
				cyl->height));
	if (fabs(denom) > 1e-6)
	{
		t = vector_dot_product(vector_subtract(top_center, ray->origin),
				cyl->axis) / denom;
		if (t >= 0 && t < t_cap)
		{
			hit = vector_add(ray->origin, vector_multiply(ray->direction, t));
			if (vector_distance(hit, top_center) <= radius)
				t_cap = t;
		}
	}
	return (t_cap);
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
