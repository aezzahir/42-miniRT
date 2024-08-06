/**
 * @file sphere.c
 * @brief Implements sphere intersection calculations
 */

#include "../miniRT.h"
#include <math.h>
#include <stdlib.h>

t_intersection *intersect_sphere(t_ray *ray, t_sphere *sphere) {
    t_vector oc = vector_subtract(ray->origin, sphere->center);
    double a = vector_dot_product(ray->direction, ray->direction);
    double b = 2.0 * vector_dot_product(oc, ray->direction);
    double c = vector_dot_product(oc, oc) - (sphere->diameter * sphere->diameter / 4.0);
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return NULL;

    double t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t < 0) {
        t = (-b + sqrt(discriminant)) / (2.0 * a);
        if (t < 0)
            return NULL;
    }

    t_intersection *intersection = malloc(sizeof(t_intersection));
    if (!intersection) return NULL;

    intersection->point = vector_add(ray->origin, vector_multiply(ray->direction, t));
    intersection->normal = vector_normalize(vector_subtract(intersection->point, sphere->center));
    intersection->object = sphere;
    intersection->t = t;
    intersection->color = sphere->color;

    return intersection;
}