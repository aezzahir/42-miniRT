/**
 * @file sphere.c
 * @brief Implements sphere intersection calculations
 */

#include "../../include/miniRT.h"

void ft_print_sphere(void *content)
{
    t_sphere *sphere;

    sphere = (t_sphere *)content;
    printf("Sphere:  center (%2f, %2f, %2f) \n", sphere->center.x,sphere->center.y, sphere->center.z);
}
t_sphere *create_sphere(t_point origin, float diameter, t_color color)
{
    t_sphere *sphere = NULL;

    sphere = (t_sphere *)malloc(sizeof(t_sphere));
    if (!sphere)
    {
        printf("malloc error in create_sphere\n");
        return (NULL);
    }
    sphere->center.x = origin.x;
    sphere->center.y = origin.y;
    sphere->center.z = origin.z;
    sphere->diameter = diameter;
    sphere->color.r = color.r;
    sphere->color.g = color.g;
    sphere->color.b = color.b;
 
    return (sphere);
}


t_intersection *intersect_sphere(t_ray *ray, t_sphere *sphere) {
    t_vector oc = vector_subtract(ray->origin, sphere->center);
    float a = vector_dot_product(ray->direction, ray->direction);
    float b = 2.0 * vector_dot_product(oc, ray->direction);
    float c = vector_dot_product(oc, oc) - (sphere->diameter * sphere->diameter / 4.0);
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return NULL;

    float t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t < 0) {
        t = (-b + sqrt(discriminant)) / (2.0 * a);
        if (t < 0)
            return NULL;
    }

    t_intersection *intersection = malloc(sizeof(t_intersection));// TODO: Free
    if (!intersection) return NULL;

    intersection->point = vector_add(ray->origin, vector_multiply(ray->direction, t));
    intersection->normal = vector_normalize(vector_subtract(intersection->point, sphere->center));
    intersection->object = sphere;
    intersection->t = t;
    intersection->color = sphere->color;

    return intersection;
}

t_intersection *intersect_lst_spheres(t_ray *ray, t_scene *scene)
{
    t_list *current = NULL;
    t_sphere *sphere;
    t_intersection *intersection, *nearest_intersection = NULL;

    if (scene->spheres && *(scene->spheres))
        current = *(scene->spheres);
    else
        return (NULL);
    while (current)
    {
        sphere = (t_sphere *)(current->content);
        intersection = intersect_sphere(ray, sphere);
        if (intersection && (!nearest_intersection || (nearest_intersection  && intersection->t < nearest_intersection->t)))
        {
            printf("nearest intersection: (%2f, %2f, %2f)", intersection->point.x, intersection->point.y, intersection->point.z);
            nearest_intersection = intersection;
        }
        current = current->next;
    }
    return (nearest_intersection);
}