#include "../../include/miniRT.h"

t_color checkerboard_pattern(t_vector point, t_color color1, t_color color2, float scale) {
    int x = floorf(point.x * scale);
    int y = floorf(point.y * scale);
    int z = floorf(point.z * scale);
    return ((x + y + z) % 2 == 0) ? color1 : color2;
}

t_vector bump_map(t_vector normal, t_vector point) {
    // Implement a simple bump map function
    float noise = sin(point.x * 10) * cos(point.y * 10) * sin(point.z * 10) * 0.1;
    return vector_normalize(vector_add(normal, vector_create(noise, noise, noise)));
}

t_color trace_ray(t_ray *ray, t_scene *scene, int depth) {
    if (depth <= 0) return scene->ambient.color;

    t_intersection *nearest_intersection = find_nearest_intersection(ray, scene);
    if (!nearest_intersection) return scene->ambient.color;

    t_vector normal = calculate_normal(nearest_intersection);
    normal = bump_map(normal, nearest_intersection->point);

    t_color surface_color = nearest_intersection->color;
    if (nearest_intersection->object_type == PLN) {
        surface_color = checkerboard_pattern(nearest_intersection->point, surface_color, color_create(1-surface_color.r, 1-surface_color.g, 1-surface_color.b), 0.1);
    }

    t_color final_color = color_scale(scene->ambient.color, scene->ambient.ratio);

    for (int i = 0; i < scene->num_lights; i++) {
        t_light *light = &scene->lights[i];
        t_vector light_dir = vector_normalize(vector_subtract(light->position, nearest_intersection->point));

        // Check for shadows
        t_ray shadow_ray = {vector_add(nearest_intersection->point, vector_multiply(normal, 0.001)), light_dir};
        if (!is_in_shadow(&shadow_ray, scene, vector_distance(light->position, nearest_intersection->point))) {
            // Diffuse component
            float diff = fmaxf(vector_dot_product(normal, light_dir), 0.0);
            t_color diffuse = color_scale(light->color, diff * light->brightness);

            // Specular component
            t_vector view_dir = vector_normalize(vector_negate(ray->direction));
            t_vector reflect_dir = vector_reflect(vector_negate(light_dir), normal);
            float spec = powf(fmaxf(vector_dot_product(view_dir, reflect_dir), 0.0), nearest_intersection->shininess);
            t_color specular = color_scale(light->color, spec * light->brightness);

            final_color = color_add(final_color, color_add(diffuse, specular));
        }
    }

    final_color = color_multiply(final_color, surface_color);

    // Reflection
    if (nearest_intersection->reflectivity > 0 && depth > 1) {
        t_vector reflect_dir = vector_reflect(ray->direction, normal);
        t_ray reflect_ray = {vector_add(nearest_intersection->point, vector_multiply(normal, 0.001)), reflect_dir};
        t_color reflect_color = trace_ray(&reflect_ray, scene, depth - 1);
        final_color = color_add(color_scale(final_color, 1 - nearest_intersection->reflectivity),
                                color_scale(reflect_color, nearest_intersection->reflectivity));
    }

    // Refraction
    if (nearest_intersection->transparency > 0 && depth > 1) {
        float refraction_ratio = nearest_intersection->inside ? nearest_intersection->refraction_index : 1.0 / nearest_intersection->refraction_index;
        t_vector refract_dir = vector_refract(ray->direction, normal, refraction_ratio);
        if (!vector_is_zero(refract_dir)) {
            t_ray refract_ray = {vector_add(nearest_intersection->point, vector_multiply(refract_dir, 0.001)), refract_dir};
            t_color refract_color = trace_ray(&refract_ray, scene, depth - 1);
            final_color = color_add(color_scale(final_color, 1 - nearest_intersection->transparency),
                                    color_scale(refract_color, nearest_intersection->transparency));
        }
    }

    free(nearest_intersection);
    return final_color;
}

bool is_in_shadow(t_ray *shadow_ray, t_scene *scene, float light_distance) {
    t_intersection *shadow_intersection = find_nearest_intersection(shadow_ray, scene);
    if (shadow_intersection && shadow_intersection->t < light_distance) {
        free(shadow_intersection);
        return true;
    }
    if (shadow_intersection) free(shadow_intersection);
    return false;
}

// Additional helper functions (implement these)
t_intersection *find_nearest_intersection(t_ray *ray, t_scene *scene);
t_vector calculate_normal(t_intersection *intersection);
t_vector vector_refract(t_vector incident, t_vector normal, float refraction_ratio);
bool vector_is_zero(t_vector v);