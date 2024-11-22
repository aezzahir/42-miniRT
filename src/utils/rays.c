#include "../../include/miniRT.h"

t_color trace_ray(t_ray *ray, t_scene *scene, int depth) 
{
    if (depth <= 0) return scene->ambient.color;

    t_intersection *intersection = ft_get_nearest_intersection(ray, scene);
    if (!intersection) return color_scale(scene->ambient.color, scene->ambient.ratio);

    t_vector normal = ft_get_surface_normal_vector(intersection);
    t_vector light_dir = vector_normalize(vector_subtract(scene->light.position, intersection->point));
    t_vector view_dir = vector_normalize(vector_negate(ray->direction));

    // Basic lighting components
    t_color ambient = calculate_ambient(scene, intersection->color);
    t_color diffuse = calculate_diffuse(scene, normal, light_dir, intersection->color);
    t_color specular = calculate_specular(scene, normal, light_dir, view_dir);

    // Shadow calculation
    ft_enable_intersecton(intersection, 0);
    float shadow_factor = calculate_shadow(scene, intersection->point, light_dir);
    ft_enable_intersecton(intersection, 1);

    // Combine basic lighting
    t_color local_color = color_add(ambient, color_scale(color_add(diffuse, specular), shadow_factor));

    free(intersection);
    return local_color;
}

t_ray ft_generate_ray(float x, float y, t_scene *scene) {
    float pixel_x = (2.0 * x / WIDTH - 1) * scene->camera.viewport_width / 2;
    float pixel_y = (1 - 2.0 * y / HEIGHT) * scene->camera.viewport_height / 2;
    
    t_vector direction = vector_normalize(
        vector_add(
            vector_add(
                vector_multiply(scene->camera.right, pixel_x),
                vector_multiply(scene->camera.up, pixel_y)
            ),
            scene->camera.forward
        )
    );
    t_vector origin = vector_add(scene->camera.position, vector_multiply(scene->camera.forward, 0.0001));
    
    return (t_ray){origin, direction};
}
