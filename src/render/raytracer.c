/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:11 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 08:51:46 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * raytracer.c
 * Core raytracing logic
 * Implements the main raytracing algorithm
 */
#include "../../include/miniRT.h"

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

void render_scene(t_scene *scene, t_mlx_data *data) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            t_color anti_aliased_color = anti_alias_pixel(scene, x, y);
            my_pixel_put(&(data->image), x, y, color_to_int(anti_aliased_color));
        }
    }
}
