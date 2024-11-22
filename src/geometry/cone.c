/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:50 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 09:33:36 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cone.c
 * @brief Implements cone intersection calculations
 */

#include "../../include/miniRT.h"

t_cone	*create_cone(t_point center, t_vector axis, float diameter,
		float height, t_color color)
{
	t_cone	*cone;

	cone = NULL;
	cone = (t_cone *)malloc(sizeof(t_cone));
	if (!cone)
	{
		printf("malloc error in create_cone\n");
		return (NULL);
	}
	cone->center = center;
	cone->axis = vector_normalize(axis);
	cone->diameter = diameter;
	cone->height = height;
	cone->color = color;
	return (cone);
}

float	check_height(float t_check, t_ray *ray, t_cone *cone)
{
	t_point	hit;
	float	height;

	if (t_check < 0)
		return (false);
	hit = vector_add(ray->origin, vector_multiply(ray->direction, t_check));
	height = vector_dot_product(vector_subtract(hit, cone->center), cone->axis);
	return (height >= 0 && height <= cone->height);
}

float	get_cone_distance(t_ray *ray, t_cone *cone)
{
	t_vector	co;
	float		tan_theta;
	float		tan_theta_squared;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t1;
	float		t2;
	float		t_near;
	float		t_far;
	float		t;
	float		denom;
	float		t_cap;
	t_point		hit;
	float		radius_at_base;

	co = vector_subtract(ray->origin, cone->center);
	tan_theta = (cone->diameter / 2) / cone->height;
	tan_theta_squared = tan_theta * tan_theta;
	a = vector_dot_product(ray->direction, ray->direction) - (1
			+ tan_theta_squared) * pow(vector_dot_product(ray->direction,
				cone->axis), 2);
	b = 2 * (vector_dot_product(ray->direction, co) - (1 + tan_theta_squared)
			* vector_dot_product(ray->direction, cone->axis)
			* vector_dot_product(co, cone->axis));
	c = vector_dot_product(co, co) - (1 + tan_theta_squared)
		* pow(vector_dot_product(co, cone->axis), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (INFINITY);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	t_near = fmin(t1, t2);
	t_far = fmax(t1, t2);
	t = INFINITY;
	if (check_height(t_near, ray, cone))
		t = t_near;
	else if (check_height(t_far, ray, cone))
		t = t_far;
	denom = vector_dot_product(ray->direction, cone->axis);
	if (fabs(denom) > 1e-6)
	{
		t_cap = vector_dot_product(vector_subtract(cone->center, ray->origin),
				cone->axis) / denom;
		if (t_cap >= 0 && t_cap < t)
		{
			hit = vector_add(ray->origin, vector_multiply(ray->direction,
						t_cap));
			radius_at_base = cone->diameter / 2;
			if (vector_distance(hit, cone->center) <= radius_at_base)
				t = t_cap;
		}
	}
	return (t);
}

t_vector	calculate_cone_normal(t_cone *cone, t_point hit_point)
{
	t_vector	cp;
	float		projection_length;
	float		radius_at_hit;
	t_vector	projection;
	t_vector	radial_vector;
	t_vector	normal;

	cp = vector_subtract(hit_point, cone->center);
	projection_length = vector_dot_product(cp, cone->axis);
	if (projection_length <= 0)
		return (vector_negate(cone->axis));
	if (projection_length >= cone->height)
		return (cone->axis);
	radius_at_hit = (cone->diameter / 2) * (1 - projection_length
			/ cone->height);
	projection = vector_multiply(cone->axis, projection_length);
	radial_vector = vector_subtract(cp, projection);
	normal = vector_subtract(radial_vector, vector_multiply(cone->axis,
				radius_at_hit));
	return (vector_normalize(normal));
}
