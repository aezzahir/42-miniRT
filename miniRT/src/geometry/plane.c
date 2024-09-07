/*
 * plane.c
 * Implements plane intersection and normal calculations
 */
#include "../../include/miniRT.h"


t_plane *create_plane(t_point point, t_vector normal, t_color color) {
    t_plane *plane = malloc(sizeof(t_plane));
    if (!plane) return NULL;
    plane->point = point;
    plane->normal = vector_normalize(normal);
    plane->color = color;
    return plane;
}


t_intersection *intersect_plane(t_ray *ray, t_plane *plane) {
    float denom = vector_dot_product(plane->normal, ray->direction);
    if (fabs(denom) > 1e-6) {
        t_vector v = vector_subtract(plane->point, ray->origin);
        float t = vector_dot_product(v, plane->normal) / denom;
        if (t >= 0) {
            t_intersection *intersection = malloc(sizeof(t_intersection));
            if (!intersection) return NULL;
            intersection->t = t;
            intersection->point = vector_add(ray->origin, vector_multiply(ray->direction, t));
            intersection->normal = plane->normal;
            intersection->color = plane->color;
            intersection->object = plane;
            intersection->object_type = PLN;
            return intersection;
        }
    }
    return NULL;
}


t_intersection *intersect_lst_planes(t_ray *ray, t_scene *scene) {
    t_list *current = *scene->planes;
    t_plane *plane;
    t_intersection *intersection, *nearest_intersection = NULL;

    while (current) {
        plane = (t_plane *)(current->content);
        intersection = intersect_plane(ray, plane);
        if (intersection && (!nearest_intersection || intersection->t < nearest_intersection->t)) {
            if (nearest_intersection) free(nearest_intersection);
            nearest_intersection = intersection;
        } else if (intersection) {
            free(intersection);
        }
        current = current->next;
    }
    return nearest_intersection;
}