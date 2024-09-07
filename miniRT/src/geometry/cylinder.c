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


t_intersection *intersect_cylinder(t_ray *ray, t_cylinder *cylinder) {
    t_vector oc = vector_subtract(ray->origin, cylinder->center);
    
    float a = vector_dot_product(ray->direction, ray->direction) - 
              pow(vector_dot_product(ray->direction, cylinder->axis), 2);
    float b = 2 * (vector_dot_product(ray->direction, oc) - 
              vector_dot_product(ray->direction, cylinder->axis) * 
              vector_dot_product(oc, cylinder->axis));
    float c = vector_dot_product(oc, oc) - 
              pow(vector_dot_product(oc, cylinder->axis), 2) - 
              pow(cylinder->diameter / 2, 2);

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return NULL;

    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);

    float t = t1 < t2 ? t1 : t2;

    if (t < 0)
        return NULL;

    t_point intersection_point = vector_add(ray->origin, vector_multiply(ray->direction, t));
    float height = vector_dot_product(vector_subtract(intersection_point, cylinder->center), cylinder->axis);

    if (height < 0 || height > cylinder->height)
        return NULL;

    t_intersection *intersection = malloc(sizeof(t_intersection));
    if (!intersection) return NULL;

    intersection->point = intersection_point;
    intersection->normal = vector_normalize(vector_subtract(
        vector_subtract(intersection->point, cylinder->center),
        vector_multiply(cylinder->axis, height)
    ));
    intersection->object = cylinder;
    intersection->t = t;
    intersection->color = cylinder->color;

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




void ft_print_cylinder(void *content)
{
    t_cylinder *cylinder;

    cylinder = (t_cylinder *)content;
    printf("Cylinder: center (%2f, %2f, %2f), axis (%2f, %2f, %2f), diameter %2f, height %2f\n",
           cylinder->center.x, cylinder->center.y, cylinder->center.z,
           cylinder->axis.x, cylinder->axis.y, cylinder->axis.z,
           cylinder->diameter, cylinder->height);
}