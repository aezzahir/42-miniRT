/*
 * raytracer.c
 * Core raytracing logic
 * Implements the main raytracing algorithm
 */
#include "../../include/miniRT.h"
t_intersection *ft_get_nearest_intersection(t_ray *ray, t_scene *scene)
{
    t_intersection *nearest_intersection = NULL;
    float nearest_t = INFINITY;

    t_intersection *sphere_intersection = intersect_lst_spheres(ray, scene);
    t_intersection *cylinder_intersection = intersect_lst_cylinders(ray, scene);
    t_intersection *plane_intersection = intersect_lst_planes(ray, scene);
    t_intersection *cone_intersection = intersect_lst_cones(ray, scene);

    

    if (sphere_intersection && sphere_intersection->t < nearest_t) {
        nearest_intersection = sphere_intersection;
        nearest_t = sphere_intersection->t;
    }
    if (cylinder_intersection && cylinder_intersection->t < nearest_t) {
        if (nearest_intersection) free(nearest_intersection);
        nearest_intersection = cylinder_intersection;
        nearest_t = cylinder_intersection->t;
    }
    if (plane_intersection && plane_intersection->t < nearest_t) {
        if (nearest_intersection) free(nearest_intersection);
        nearest_intersection = plane_intersection;
        nearest_t = plane_intersection->t;
    }
    if (cone_intersection && cone_intersection->t < nearest_t) {
        if (nearest_intersection) free(nearest_intersection);
        nearest_intersection = cone_intersection;
        nearest_t = cone_intersection->t;
    }
    return (nearest_intersection);
}
t_vector ft_get_surface_normal_vector(t_intersection *inter)
{
    t_vector normal =  (t_vector){0, 0, 0};
    if (!inter)
         return (normal);
    switch (inter->object_type) {
        case SPH: {
            t_sphere *sphere = (t_sphere *)inter->object;
            normal = vector_normalize(vector_subtract(inter->point, sphere->center));
            break;
        }
        case CYL: {
            t_cylinder *cylinder = (t_cylinder *)inter->object;
            normal = calculate_cylinder_normal(cylinder, inter->point);
            break;
        }
        case PLN: {
            normal = ((t_plane *)inter->object)->normal;
            break;
        }
        case CONE:
        {
            t_cone *cone = (t_cone *)inter->object;
            normal = calculate_cone_normal(cone, inter->point);
            break;
        }
        default:
           break;;
    }
    return (normal);
}
t_ray ft_generate_ray(int x, int y, t_scene *scene) {
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

t_color trace_ray(t_ray *ray, t_scene *scene, int depth)
{
    t_vector normal;
    t_intersection *nearest_intersection;
    if (depth < 0) return scene->ambient.color;
    nearest_intersection = ft_get_nearest_intersection(ray, scene);
    normal = ft_get_surface_normal_vector(nearest_intersection);


    if (!nearest_intersection) return scene->ambient.color;

   

    t_vector light_dir = vector_normalize(vector_subtract(scene->light.position, nearest_intersection->point));

    // Ambient component
    t_color ambient = color_scale(scene->ambient.color, scene->ambient.ratio);

    // Diffuse component
    float diff = fmaxf(vector_dot_product(normal, light_dir), 0.0);
    t_color diffuse = color_scale(scene->light.color, diff * scene->light.brightness);

    // Specular component (Phong reflection model)
    t_vector view_dir = vector_normalize(vector_negate(ray->direction));
    t_vector reflect_dir = vector_reflect(vector_negate(light_dir), normal);
    float spec = pow(fmaxf(vector_dot_product(view_dir, reflect_dir), 0.0), 32);
    t_color specular = color_scale(scene->light.color, 0.5 * spec * scene->light.brightness);

    // Combine colors
    t_color final_color = color_add(ambient, color_add(diffuse, specular));
    final_color = color_multiply(final_color, nearest_intersection->color);

    // // Check for shadows
    // t_ray shadow_ray = {nearest_intersection->point, light_dir};
    // t_intersection *shadow_intersection = intersect_lst_spheres(&shadow_ray, scene);
    // if (!shadow_intersection) 
    //     shadow_intersection = intersect_lst_cylinders(&shadow_ray, scene);
    // if (!shadow_intersection) 
    //     shadow_intersection = intersect_lst_planes(&shadow_ray, scene);
    
    // if (shadow_intersection) {
    //     float light_distance = vector_length(vector_subtract(scene->light.position, nearest_intersection->point));
    //     if (shadow_intersection->t < light_distance) {
    //         // Point is in shadow, only use ambient light
    //         final_color = ambient;
    //     }
    //     free(shadow_intersection);
    // }

    free(nearest_intersection);
    return final_color;
}



void render_scene(t_scene *scene, t_mlx_data *data) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            t_ray ray = ft_generate_ray(x, y, scene);
            t_color color = trace_ray(&ray, scene, MAX_DEPTH);
            my_pixel_put(&(data->image), x, y, color_to_int(color));
        }
    }
}
