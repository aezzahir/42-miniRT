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
void ft_enable_intersecton(t_intersection *inter, int value)
{
    if (!inter)
         return;
    switch (inter->object_type) {
        case SPH: {
            t_sphere *sphere = (t_sphere *)inter->object;
            sphere->enable_intersection = value;
            break;
        }
        case CYL: {
            t_cylinder *cylinder = (t_cylinder *)inter->object;
            cylinder->enable_intersection = value;
            break;
        }
        case PLN: {
            t_plane *plane = (t_plane *)inter->object;
            plane->enable_intersection = value;
            break;
        }
        case CONE:
        {
            t_cone *cone = (t_cone *)inter->object;
            cone->enable_intersection = value;
            break;
        }
        default:
           break;;
    }
    return ;
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


t_color trace_ray(t_ray *ray, t_scene *scene, int depth) {
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

    // // Reflection and refraction for water-like materials
    // t_color reflection_color = {0, 0, 0};
    // t_color refraction_color = {0, 0, 0};

    // if (intersection->object_type == SPH || intersection->object_type == CYL) {  // Assume these are water-like
    //     reflection_color = calculate_reflection(ray, intersection, scene, depth);
    //     refraction_color = calculate_refraction(ray, intersection, scene, depth);

    //     local_color = color_scale(local_color, 1 - WATER_TRANSPARENCY - WATER_REFLECTIVITY);
    //     local_color = color_add(local_color, color_scale(reflection_color, WATER_REFLECTIVITY));
    //     local_color = color_add(local_color, color_scale(refraction_color, WATER_TRANSPARENCY));
    // }

    free(intersection);
    return local_color;
}

#define AA_SAMPLES 2  // 4x4 supersampling

t_color anti_alias_pixel(t_scene *scene, int x, int y) {
    t_color color_sum = {0, 0, 0};
    float r_sum = 0, g_sum = 0, b_sum = 0;

    for (int dx = 0; dx < AA_SAMPLES; dx++) {
        for (int dy = 0; dy < AA_SAMPLES; dy++) {
            float subpixel_x = x + (dx + 0.5f) / AA_SAMPLES;
            float subpixel_y = y + (dy + 0.5f) / AA_SAMPLES;

            t_ray ray = ft_generate_ray(subpixel_x, subpixel_y, scene);
            t_color subpixel_color = trace_ray(&ray, scene, MAX_DEPTH);

            r_sum += subpixel_color.r;
            g_sum += subpixel_color.g;
            b_sum += subpixel_color.b;
        }
    }

    int total_samples = AA_SAMPLES * AA_SAMPLES;
    color_sum.r = r_sum / total_samples;
    color_sum.g = g_sum / total_samples;
    color_sum.b = b_sum / total_samples;

    return color_sum;
}

void render_scene(t_scene *scene, t_mlx_data *data) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            t_color anti_aliased_color = anti_alias_pixel(scene, x, y);
            my_pixel_put(&(data->image), x, y, color_to_int(anti_aliased_color));
        }
    }
}

void xrender_scene(t_scene *scene, t_mlx_data *data) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            t_ray ray = ft_generate_ray(x, y, scene);
            t_color color = trace_ray(&ray, scene, MAX_DEPTH);
            my_pixel_put(&(data->image), x, y, color_to_int(color));
        }
    }
}