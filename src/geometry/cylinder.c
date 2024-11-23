/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:54 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 22:06:09 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * cylinder.c
 * Implements cylinder intersection and normal calculations
 */

#include "../../include/miniRT.h"

t_vector get_perpendicular_vector(t_vector v, t_vector axis)
{
    return vector_subtract(v, vector_multiply(axis, vector_dot_product(v, axis)));
}

float calculate_discriminant(t_vector v_dir_perp, t_vector oc_perp, float radius)
{
    float   a;
    float   b;
    float   c;

    a = vector_dot_product(v_dir_perp, v_dir_perp);
    b = 2 * vector_dot_product(v_dir_perp, oc_perp);
    c = vector_dot_product(oc_perp, oc_perp) - radius * radius;
    return b * b - 4 * a * c;
}

float solve_quadratic(float a, float b, float discriminant)
{
    float   t_body1;
    float   t_body2;

    t_body1 = (-b - sqrt(discriminant)) / (2 * a);
    t_body2 = (-b + sqrt(discriminant)) / (2 * a);
    return (t_body1 >= 0) ? t_body1 : t_body2;
}

bool is_within_body(t_point body_hit, t_cylinder *cyl)
{
    float   body_height;

    	body_height = vector_dot_product(vector_subtract(
        body_hit, cyl->center), cyl->axis);
    return (body_height >= 0 && body_height <= cyl->height);
}

float get_bottom_cap_distance(t_ray *ray, t_cylinder *cyl, float denom)
{
    float t;
    t_point hit;

    if (fabs(denom) > 1e-6)
    {
        t = vector_dot_product(vector_subtract(cyl->center, ray->origin), cyl->axis) / denom;
        if (t >= 0)
        {
            hit = vector_add(ray->origin, vector_multiply(ray->direction, t));
            if (vector_distance(hit, cyl->center) <= cyl->diameter / 2)
                return t;
        }
    }

    return INFINITY;
}

float get_top_cap_distance(t_ray *ray, t_cylinder *cyl, float denom)
{
    t_point top_center = vector_add(cyl->center, vector_multiply(cyl->axis, cyl->height));
    float t;
    t_point hit;

    if (fabs(denom) > 1e-6)
    {
        t = vector_dot_product(vector_subtract(top_center, ray->origin), cyl->axis) / denom;
        if (t >= 0)
        {
            hit = vector_add(ray->origin, vector_multiply(ray->direction, t));
            if (vector_distance(hit, top_center) <= cyl->diameter / 2)
                return t;
        }
    }

    return INFINITY;
}


float compute_cap_distance(t_ray *ray, t_cylinder *cyl)
{
    float denom = vector_dot_product(ray->direction, cyl->axis);
    float t_bottom = get_bottom_cap_distance(ray, cyl, denom);

    if (t_bottom < INFINITY)
        return t_bottom;

    return get_top_cap_distance(ray, cyl, denom);
}

float compute_body_distance(t_ray *ray, t_cylinder *cyl)
{
    t_vector oc = vector_subtract(ray->origin, cyl->center);
    t_vector v_dir_perpendicular = get_perpendicular_vector(ray->direction, cyl->axis);
    t_vector oc_perpendicular = get_perpendicular_vector(oc, cyl->axis);
    float radius = cyl->diameter / 2;

    float discriminant = calculate_discriminant(v_dir_perpendicular, oc_perpendicular, radius);
    if (discriminant < 0)
        return -1;

    float a = vector_dot_product(v_dir_perpendicular, v_dir_perpendicular);
    float b = 2 * vector_dot_product(v_dir_perpendicular, oc_perpendicular);
    float t_body = solve_quadratic(a, b, discriminant);

    if (t_body >= 0)
    {
        t_point body_hit = vector_add(ray->origin, vector_multiply(ray->direction, t_body));
        if (is_within_body(body_hit, cyl))
            return t_body;
    }

    return -1;
}

float get_cylinder_distance(t_ray *ray, t_cylinder *cyl)
{
    float t_body = compute_body_distance(ray, cyl);
    if (t_body >= 0)
        return t_body;

    return compute_cap_distance(ray, cyl);
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
