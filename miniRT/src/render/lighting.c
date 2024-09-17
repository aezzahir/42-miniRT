/*
 * lighting.c
 * Implements lighting calculations
 * Manages ambient, diffuse, and shadow computations
 */
#include "../../include/miniRT.h"

t_color calculate_ambient(t_scene *scene, t_color object_color) {
    return color_multiply(color_scale(scene->ambient.color, scene->ambient.ratio), object_color);
}

t_color calculate_diffuse(t_scene *scene, t_vector normal, t_vector light_dir, t_color object_color) {
    float diff = fmaxf(vector_dot_product(normal, light_dir), 0.0);
    return color_multiply(color_scale(scene->light.color, diff * scene->light.brightness), object_color);
}

t_color calculate_specular(t_scene *scene, t_vector normal, t_vector light_dir, t_vector view_dir) {
    t_vector reflect_dir = vector_reflect(vector_negate(light_dir), normal);
    float spec = pow(fmaxf(vector_dot_product(view_dir, reflect_dir), 0.0), 200);
    return color_scale(scene->light.color, 0.5 * spec * scene->light.brightness);
}

float calculate_shadow(t_scene *scene, t_point hit_point, t_vector light_dir) {
    float light_distance = vector_length(vector_subtract(scene->light.position, hit_point));
    
    t_ray shadow_ray = {hit_point, light_dir};
    t_intersection *shadow_intersection = ft_get_nearest_intersection(&shadow_ray, scene);
    
    if (shadow_intersection && shadow_intersection->t < light_distance) {
        free(shadow_intersection);
        return 0.0;  // Full shadow
    }
    
    if (shadow_intersection) {
        free(shadow_intersection);
    }
    
    return 1.0;  // No shadow
}

t_color calculate_reflection(t_ray *ray, t_intersection *intersection, t_scene *scene, int depth) {
    t_vector reflect_dir = vector_reflect(ray->direction, intersection->normal);
    t_ray reflect_ray = {intersection->point, reflect_dir};
    return trace_ray(&reflect_ray, scene, depth - 1);
}

t_color calculate_refraction(t_ray *ray, t_intersection *intersection, t_scene *scene, int depth) {
    float eta = 1.0 / WATER_REFRACTIVE_INDEX;
    t_vector refract_dir;
    if (vector_refract(ray->direction, intersection->normal, eta, &refract_dir)) {
        t_ray refract_ray = {intersection->point, refract_dir};
        return trace_ray(&refract_ray, scene, depth - 1);
    }
    return (t_color){0, 0, 0};
}

int vector_refract(t_vector incident, t_vector normal, float eta, t_vector *refracted) {
    float dot = vector_dot_product(incident, normal);
    float k = 1.0 - eta * eta * (1.0 - dot * dot);
    if (k < 0) {
        return 0;  // Total internal reflection
    }
    *refracted = vector_subtract(
        vector_multiply(incident, eta),
        vector_multiply(normal, (eta * dot + sqrt(k)))
    );
    *refracted = vector_normalize(*refracted);
    return 1;
}