/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:11 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/20 22:13:12 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * raytracer.c
 * Core raytracing logic
 * Implements the main raytracing algorithm
 */
#include "../../include/miniRT.h"







// Helper function to get distance for any object type
float get_object_distance(t_ray *ray, void *object, t_object_type type)
{
    if (type == SPH)
        return get_sphere_distance(ray, (t_sphere *)object);
    if (type == CYL)
        return get_cylinder_distance(ray, (t_cylinder *)object);
    if (type == PLN)
        return get_plane_distance(ray, (t_plane *)object);
    if (type == CONE)
        return get_cone_distance(ray, (t_cone *)object);
    return INFINITY;
}

t_intersection *ft_get_nearest_intersection(t_ray *ray, t_scene *scene)
{
    t_hit_info nearest = {NULL, INFINITY, NONE};
    float dist;

    // Check spheres
    t_list *current = *(scene->spheres);
    while (current)
    {
        t_sphere *sphere = (t_sphere *)(current->content);
        if (sphere->enable_intersection && 
            (dist = get_sphere_distance(ray, sphere)) < nearest.distance)
        {
            nearest.object = sphere;
            nearest.distance = dist;
            nearest.type = SPH;
        }
        current = current->next;
    }

    // Check cylinders
    current = *(scene->cylinders);
    while (current)
    {
        t_cylinder *cylinder = (t_cylinder *)(current->content);
        if (cylinder->enable_intersection && 
            (dist = get_cylinder_distance(ray, cylinder)) < nearest.distance)
        {
            nearest.object = cylinder;
            nearest.distance = dist;
            nearest.type = CYL;
        }
        current = current->next;
    }

    // Check planes
    current = *(scene->planes);
    while (current)
    {
        t_plane *plane = (t_plane *)(current->content);
        if (plane->enable_intersection && 
            (dist = get_plane_distance(ray, plane)) < nearest.distance)
        {
            nearest.object = plane;
            nearest.distance = dist;
            nearest.type = PLN;
        }
        current = current->next;
    }

    // Check cones
    current = *(scene->cones);
    while (current)
    {
        t_cone *cone = (t_cone *)(current->content);
        if (cone->enable_intersection && 
            (dist = get_cone_distance(ray, cone)) < nearest.distance)
        {
            nearest.object = cone;
            nearest.distance = dist;
            nearest.type = CONE;
        }
        current = current->next;
    }

    // If no intersection found
    if (nearest.distance == INFINITY)
        return NULL;

    // Create intersection only for the nearest object
    return create_intersection(ray, &nearest);
}



// Create intersection only when needed
t_intersection *create_intersection(t_ray *ray, t_hit_info *hit)
{
    t_intersection *inter = malloc(sizeof(t_intersection));
    if (!inter)
        return NULL;

    inter->t = hit->distance;
    inter->point = vector_add(ray->origin, vector_multiply(ray->direction, hit->distance));
    inter->object = hit->object;
    inter->object_type = hit->type;

    // Set color and normal based on object type
if (hit->type == SPH)
{
    inter->color = ((t_sphere *)hit->object)->color;
    inter->normal = vector_normalize(vector_subtract(inter->point,
        ((t_sphere *)hit->object)->center));
}
else if (hit->type == CYL)
{
    inter->color = ((t_cylinder *)hit->object)->color;
    inter->normal = calculate_cylinder_normal(hit->object, inter->point);
}
else if (hit->type == PLN)
{
    inter->color = ((t_plane *)hit->object)->color;
    inter->normal = ((t_plane *)hit->object)->normal;
}
else if (hit->type == CONE)
{
    inter->color = ((t_cone *)hit->object)->color;
    inter->normal = calculate_cone_normal(hit->object, inter->point);
}

    return inter;
}
t_vector ft_get_surface_normal_vector(t_intersection *inter)
{
    t_vector normal =  (t_vector){0, 0, 0};
    if (!inter)
         return (normal);
    if (inter->object_type == SPH) 
    {
    t_sphere *sphere = (t_sphere *)inter->object;
    normal = vector_normalize(vector_subtract(inter->point, sphere->center));
    }
    else if (inter->object_type == CYL)
    {
    t_cylinder *cylinder = (t_cylinder *)inter->object;
    normal = calculate_cylinder_normal(cylinder, inter->point);
    }
    else if (inter->object_type == PLN)
    {
    normal = ((t_plane *)inter->object)->normal;
    }
    else if (inter->object_type == CONE)
    {
    t_cone *cone = (t_cone *)inter->object;
    normal = calculate_cone_normal(cone, inter->point);
    }
    return (normal);
}
void ft_enable_intersecton(t_intersection *inter, int value)
{
    if (!inter)
         return;
    if (inter->object_type == SPH)
    {
    t_sphere *sphere = (t_sphere *)inter->object;
    sphere->enable_intersection = value;
    }
    else if (inter->object_type == CYL)
    {
    t_cylinder *cylinder = (t_cylinder *)inter->object;
    cylinder->enable_intersection = value;
    }
    else if (inter->object_type == PLN)
    {
    t_plane *plane = (t_plane *)inter->object;
    plane->enable_intersection = value;
    }
    else if (inter->object_type == CONE)
    {
    t_cone *cone = (t_cone *)inter->object;
    cone->enable_intersection = value;
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