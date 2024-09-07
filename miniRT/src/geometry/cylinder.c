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


t_intersection *intersect_cylinder(t_ray *ray, t_cylinder *cyl) {
    t_vector oc = vector_subtract(ray->origin, cyl->center);
    float radius = cyl->diameter / 2;
    
    // Cylinder body intersection
    t_vector abc = vector_subtract(ray->direction, 
                    vector_multiply(cyl->axis, vector_dot_product(ray->direction, cyl->axis)));
    t_vector def = vector_subtract(oc, 
                    vector_multiply(cyl->axis, vector_dot_product(oc, cyl->axis)));
    
    float a = vector_dot_product(abc, abc);
    float b = 2 * vector_dot_product(abc, def);
    float c = vector_dot_product(def, def) - radius * radius;
    
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return NULL;
    
    float t_body = (-b - sqrt(discriminant)) / (2 * a);
    if (t_body < 0) t_body = (-b + sqrt(discriminant)) / (2 * a);
    
    // Cap intersections
    float t_bottom = (vector_dot_product(vector_subtract(cyl->center, ray->origin), cyl->axis) /
                     vector_dot_product(ray->direction, cyl->axis));
    float t_top = (vector_dot_product(vector_subtract(vector_add(cyl->center, vector_multiply(cyl->axis, cyl->height)), ray->origin), cyl->axis) /
                  vector_dot_product(ray->direction, cyl->axis));

    t_point p_bottom = vector_add(ray->origin, vector_multiply(ray->direction, t_bottom));
    t_point p_top = vector_add(ray->origin, vector_multiply(ray->direction, t_top));

    bool valid_bottom = (vector_distance(p_bottom, cyl->center) <= radius);
    bool valid_top = (vector_distance(p_top, vector_add(cyl->center, vector_multiply(cyl->axis, cyl->height))) <= radius);

    float t = INFINITY;
    int hit_type = 0; // 0: body, 1: bottom cap, 2: top cap

    if (t_body > 0) {
        t_point hit_body = vector_add(ray->origin, vector_multiply(ray->direction, t_body));
        float body_height = vector_dot_product(vector_subtract(hit_body, cyl->center), cyl->axis);
        if (body_height >= 0 && body_height <= cyl->height) {
            t = t_body;
            hit_type = 0;
        }
    }

    if (valid_bottom && t_bottom > 0 && t_bottom < t) {
        t = t_bottom;
        hit_type = 1;
    }

    if (valid_top && t_top > 0 && t_top < t) {
        t = t_top;
        hit_type = 2;
    }

    if (t == INFINITY) return NULL;

    t_intersection *intersection = malloc(sizeof(t_intersection));
    if (!intersection) return NULL;
    
    intersection->point = vector_add(ray->origin, vector_multiply(ray->direction, t));
    intersection->t = t;
    intersection->object = cyl;
    intersection->color = cyl->color;
    intersection->object_type = CYL;
    
    // Calculate normal
    if (hit_type == 0) {
        // Hit on cylinder body
        t_vector cp = vector_subtract(intersection->point, cyl->center);
        t_vector projection = vector_multiply(cyl->axis, vector_dot_product(cp, cyl->axis));
        intersection->normal = vector_normalize(vector_subtract(cp, projection));
    } else if (hit_type == 1) {
        // Hit on bottom cap
        intersection->normal = vector_negate(cyl->axis);
    } else {
        // Hit on top cap
        intersection->normal = cyl->axis;
    }
    
    return intersection;
}

t_intersection *intersect_lst_cylinders(t_ray *ray, t_scene *scene)
{
    t_list *current = NULL;
    t_cylinder *cylinder;
    t_intersection *intersection, *nearest_intersection = NULL;

    if (scene->cylinders && *(scene->cylinders))
        current = *(scene->cylinders);
    else
        return (NULL);

    while (current)
    {
        cylinder = (t_cylinder *)(current->content);
        intersection = intersect_cylinder(ray, cylinder);
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

t_vector calculate_cylinder_normal(t_cylinder *cylinder, t_point intersection_point) {
    t_vector cp = vector_subtract(intersection_point, cylinder->center);
    float dot = vector_dot_product(cp, cylinder->axis);
    t_vector projection = vector_multiply(cylinder->axis, dot);
    return vector_normalize(vector_subtract(cp, projection));
}


void ft_print_cylinder(void *content)
{
    t_cylinder *cylinder;

    cylinder = (t_cylinder *)content;
    printf("Cylinder: center (%2f, %2f, %2f), axis (%2f, %2f, %2f), diameter %2f, height %2f\n",
           cylinder->center.x, cylinder->center.y, cylinder->center.z,
           cylinder->axis.x, cylinder->axis.y, cylinder->axis.z,
           cylinder->diameter, cylinder->height);
}