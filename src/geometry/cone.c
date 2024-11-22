/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:50 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 05:21:24 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cone.c
 * @brief Implements cone intersection calculations
 */

#include "../../include/miniRT.h"

void ft_print_cone(void *content)
{
    t_cone *cone;

    cone = (t_cone *)content;
    printf("Cone: base center (%2f, %2f, %2f), axis (%2f, %2f, %2f), diameter %2f, height %2f\n", 
           cone->center.x, cone->center.y, cone->center.z,
           cone->axis.x, cone->axis.y, cone->axis.z,
           cone->diameter, cone->height);
}

t_cone *create_cone(t_point center, t_vector axis, float diameter, float height, t_color color)
{
    t_cone *cone = NULL;

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

float check_height(float t_check, t_ray *ray, t_cone *cone) {
    if (t_check < 0)
        return false;
    t_point hit = vector_add(ray->origin, vector_multiply(ray->direction, t_check));
    float height = vector_dot_product(vector_subtract(hit, cone->center), cone->axis);
    return (height >= 0 && height <= cone->height);
}

float get_cone_distance(t_ray *ray, t_cone *cone)
{
    t_vector co = vector_subtract(ray->origin, cone->center);
    float tan_theta = (cone->diameter / 2) / cone->height;
    float tan_theta_squared = tan_theta * tan_theta;
    
    // Calculate quadratic equation coefficients
    float a = vector_dot_product(ray->direction, ray->direction) - 
              (1 + tan_theta_squared) * pow(vector_dot_product(ray->direction, cone->axis), 2);
              
    float b = 2 * (vector_dot_product(ray->direction, co) - 
              (1 + tan_theta_squared) * vector_dot_product(ray->direction, cone->axis) * 
              vector_dot_product(co, cone->axis));
              
    float c = vector_dot_product(co, co) - 
              (1 + tan_theta_squared) * pow(vector_dot_product(co, cone->axis), 2);

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return INFINITY;

    // Find the nearest intersection point
    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);
    
    // Order intersections
    float t_near = fmin(t1, t2);
    float t_far = fmax(t1, t2);
    
    // Check both intersections for validity
    float t = INFINITY;
    
    // Function to check if a intersection point is within cone height

    
    // Check near intersection first
    if (check_height(t_near, ray, cone))
        t = t_near;
    // If near intersection is not valid, check far intersection
    else if (check_height(t_far, ray, cone))
        t = t_far;

    // Check base cap
    float denom = vector_dot_product(ray->direction, cone->axis);
    if (fabs(denom) > 1e-6)
    {
        float t_cap = vector_dot_product(vector_subtract(cone->center, ray->origin), cone->axis) / denom;
        if (t_cap >= 0 && t_cap < t)
        {
            t_point hit = vector_add(ray->origin, vector_multiply(ray->direction, t_cap));
            float radius_at_base = cone->diameter / 2;
            if (vector_distance(hit, cone->center) <= radius_at_base)
                t = t_cap;
        }
    }

    return t;
}

t_vector calculate_cone_normal(t_cone *cone, t_point hit_point) {
    // Vector from cone base center to hit point
    t_vector cp = vector_subtract(hit_point, cone->center);
    
    // Project the vector cp onto the cone's axis
    float projection_length = vector_dot_product(cp, cone->axis);
    
    // If the hit is on the base cap
    if (projection_length <= 0) {
        return vector_negate(cone->axis);  // Normal is opposite to the cone's axis for the base cap
    }
    
    // If the hit is on the apex (top point)
    if (projection_length >= cone->height) {
        return cone->axis;  // Normal is the same as the cone's axis for the apex
    }
    
    // Hit on the cone surface
    // Calculate the radius at the hit point
    float radius_at_hit = (cone->diameter / 2) * (1 - projection_length / cone->height);
    
    // Calculate the normal on the cone surface
    t_vector projection = vector_multiply(cone->axis, projection_length);
    t_vector radial_vector = vector_subtract(cp, projection);
    t_vector normal = vector_subtract(radial_vector, vector_multiply(cone->axis, radius_at_hit));
    
    return vector_normalize(normal);
}

