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

t_intersection *intersect_cone(t_ray *ray, t_cone *cone)
{
    t_vector co = vector_subtract(ray->origin, cone->center);
    float tan_theta = (cone->diameter / 2) / cone->height;
    float tan_theta_squared = tan_theta * tan_theta;

    if (cone->enable_intersection != 1)
        return (NULL);
    float a = vector_dot_product(ray->direction, ray->direction) - 
              (1 + tan_theta_squared) * pow(vector_dot_product(ray->direction, cone->axis), 2);
    float b = 2 * (vector_dot_product(ray->direction, co) - 
              (1 + tan_theta_squared) * vector_dot_product(ray->direction, cone->axis) * vector_dot_product(co, cone->axis));
    float c = vector_dot_product(co, co) - 
              (1 + tan_theta_squared) * pow(vector_dot_product(co, cone->axis), 2);

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return NULL;

    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);

    float t = (t1 < t2 && t1 > 0) ? t1 : t2;

    if (t < 0)
        return NULL;

    t_point hit_point = vector_add(ray->origin, vector_multiply(ray->direction, t));
    float height_hit = vector_dot_product(vector_subtract(hit_point, cone->center), cone->axis);

    if (height_hit < 0 || height_hit > cone->height)
        return NULL;

    t_intersection *intersection = malloc(sizeof(t_intersection)); // TODO: Free
    if (!intersection) return NULL;

    intersection->point = hit_point;
    t_vector cp = vector_subtract(intersection->point, cone->center);
    t_vector n = vector_subtract(cp, vector_multiply(cone->axis, vector_dot_product(cp, cone->axis)));
    intersection->normal = vector_normalize(n);
    intersection->object = cone;
    intersection->t = t;
    intersection->color = cone->color;
    intersection->object_type = CONE;

    return intersection;
}

t_intersection *intersect_lst_cones(t_ray *ray, t_scene *scene)
{
    t_list *current = NULL;
    t_cone *cone;
    t_intersection *intersection, *nearest_intersection = NULL;

    if (scene->cones && *(scene->cones))
        current = *(scene->cones);
    else
        return (NULL);
    while (current)
    {
        cone = (t_cone *)(current->content);
        intersection = intersect_cone(ray, cone);
        if (intersection && (!nearest_intersection || (nearest_intersection && intersection->t < nearest_intersection->t)))
        {
            if (nearest_intersection)
                free(nearest_intersection);
            nearest_intersection = intersection;
        }
        else if (intersection)
        {
            free(intersection);
        }
        current = current->next;
    }
    return (nearest_intersection);
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