/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:50 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 22:14:03 by iben-haj         ###   ########.fr       */
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

float	compute_cone_cap_intersection(t_ray *ray, t_cone *cone)
{
	float	denom;
	float	t_cap;
	t_point	hit;
	float	radius_at_base;

	denom = vector_dot_product(ray->direction, cone->axis);
	if (fabs(denom) <= 1e-6)
		return (INFINITY);
	t_cap = vector_dot_product(vector_subtract(cone->center, ray->origin),
			cone->axis) / denom;
	if (t_cap < 0)
		return (INFINITY);
	hit = vector_add(ray->origin, vector_multiply(ray->direction, t_cap));
	radius_at_base = cone->diameter / 2;
	if (vector_distance(hit, cone->center) <= radius_at_base)
		return (t_cap);
	return (INFINITY);
}

t_quadratic_params	calculate_cone_quadratic_params(t_ray *ray, t_cone *cone)
{
	t_vector			co;
	float				tan_theta;
	float				tan_theta_squared;
	t_quadratic_params	params;

	co = vector_subtract(ray->origin, cone->center);
	tan_theta = (cone->diameter / 2) / cone->height;
	tan_theta_squared = tan_theta * tan_theta;
	params.a = vector_dot_product(ray->direction, ray->direction) - (1
			+ tan_theta_squared) * pow(vector_dot_product(ray->direction,
				cone->axis), 2);
	params.b = 2 * (vector_dot_product(ray->direction, co) - (1
				+ tan_theta_squared) * vector_dot_product(ray->direction,
				cone->axis) * vector_dot_product(co, cone->axis));
	params.c = vector_dot_product(co, co) - (1 + tan_theta_squared)
		* pow(vector_dot_product(co, cone->axis), 2);
	params.discriminant = params.b * params.b - 4 * params.a * params.c;
	return (params);
}

float	find_cone_intersection(t_ray *ray, t_cone *cone,
		t_quadratic_params *params)
{
	float	t1;
	float	t2;
	float	t_near;
	float	t_far;

	t1 = (-params->b - sqrt(params->discriminant)) / (2 * params->a);
	t2 = (-params->b + sqrt(params->discriminant)) / (2 * params->a);
	t_near = fmin(t1, t2);
	t_far = fmax(t1, t2);
	if (check_height(t_near, ray, cone))
		return (t_near);
	if (check_height(t_far, ray, cone))
		return (t_far);
	return (INFINITY);
}

float	compute_cone_body_intersection(t_ray *ray, t_cone *cone)
{
	t_quadratic_params	params;

	params = calculate_cone_quadratic_params(ray, cone);
	if (params.discriminant < 0)
		return (INFINITY);
	return (find_cone_intersection(ray, cone, &params));
}

float	get_cone_distance(t_ray *ray, t_cone *cone)
{
	float	t;
	float	t_cap;

	t = compute_cone_body_intersection(ray, cone);
	t_cap = compute_cone_cap_intersection(ray, cone);
	if (t_cap >= 0 && t_cap < t)
		t = t_cap;
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
