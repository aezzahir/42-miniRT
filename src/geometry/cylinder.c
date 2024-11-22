/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:54 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 05:22:59 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * cylinder.c
 * Implements cylinder intersection and normal calculations
 */
 
#include "../../include/miniRT.h"

t_cylinder *create_cylinder(t_point center, t_vector axis, float diameter, float height, t_color color)
{
    t_cylinder *cylinder = NULL;

    cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
    if (!cylinder)
    {
        printf("malloc error in create_cylinder\n");
        return (NULL);
    }

    cylinder->center = center;
    cylinder->axis = vector_normalize(axis);  // Ensure the axis is normalized
    cylinder->diameter = diameter;
    cylinder->height = height;
    cylinder->color = color;

    return (cylinder);
}


float get_cylinder_distance(t_ray *ray, t_cylinder *cyl)
{
    t_vector oc = vector_subtract(ray->origin, cyl->center);
    float radius = cyl->diameter / 2;
    
    // Calculate body intersection
    t_vector v_dir_perpendicular = vector_subtract(ray->direction, 
        vector_multiply(cyl->axis, vector_dot_product(ray->direction, cyl->axis)));
    t_vector oc_perpendicular = vector_subtract(oc, 
        vector_multiply(cyl->axis, vector_dot_product(oc, cyl->axis)));
    
    float a = vector_dot_product(v_dir_perpendicular, v_dir_perpendicular);
    float b = 2 * vector_dot_product(v_dir_perpendicular, oc_perpendicular);
    float c = vector_dot_product(oc_perpendicular, oc_perpendicular) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return INFINITY;

    float t_body1 = (-b - sqrt(discriminant)) / (2 * a);
    float t_body2 = (-b + sqrt(discriminant)) / (2 * a);
    float t_body = (t_body1 >= 0) ? t_body1 : t_body2;

    // Check if body intersection is within cylinder height
    if (t_body >= 0)
    {
        t_point body_hit = vector_add(ray->origin, vector_multiply(ray->direction, t_body));
        float body_height = vector_dot_product(vector_subtract(body_hit, cyl->center), cyl->axis);
        if (body_height >= 0 && body_height <= cyl->height)
            return t_body;
    }

    // Calculate cap intersections
    float t_cap = INFINITY;
    
    // Bottom cap
    float denom = vector_dot_product(ray->direction, cyl->axis);
    if (fabs(denom) > 1e-6)
    {
        float t = vector_dot_product(vector_subtract(cyl->center, ray->origin), cyl->axis) / denom;
        if (t >= 0)
        {
            t_point hit = vector_add(ray->origin, vector_multiply(ray->direction, t));
            if (vector_distance(hit, cyl->center) <= radius)
                t_cap = t;
        }
    }

    // Top cap
    t_point top_center = vector_add(cyl->center, vector_multiply(cyl->axis, cyl->height));
    if (fabs(denom) > 1e-6)
    {
        float t = vector_dot_product(vector_subtract(top_center, ray->origin), cyl->axis) / denom;
        if (t >= 0 && t < t_cap)
        {
            t_point hit = vector_add(ray->origin, vector_multiply(ray->direction, t));
            if (vector_distance(hit, top_center) <= radius)
                t_cap = t;
        }
    }

    return t_cap;
}


t_vector calculate_cylinder_normal(t_cylinder *cyl, t_point hit_point) {
    // Vector from cylinder base center to hit point
    t_vector cp = vector_subtract(hit_point, cyl->center);
    
    // Project the vector cp onto the cylinder's axis
    float projection_length = vector_dot_product(cp, cyl->axis);
    
    // If the hit is on the bottom cap
    if (projection_length <= 0) {
        return vector_negate(cyl->axis);  // Normal is opposite to the cylinder's axis for the bottom cap
    }
    
    // If the hit is on the top cap
    if (projection_length >= cyl->height) {
        return cyl->axis;  // Normal is the same as the cylinder's axis for the top cap
    }
    
    // Hit on the cylinder body
    // Remove the component of cp along the axis to get the normal on the cylinder body
    t_vector projection = vector_multiply(cyl->axis, projection_length);
    t_vector normal = vector_subtract(cp, projection);  // This gives the vector perpendicular to the axis
    return vector_normalize(normal);  // Normalize the result to get the normal direction
}
