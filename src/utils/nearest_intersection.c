/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:27 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 17:26:20 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
// Check intersection with a sphere
float check_sphere_intersection(t_ray *ray, t_list *current, t_hit_info *nearest)
{
    t_sphere *sphere = (t_sphere *)(current->content);
    float dist;

    if (sphere->enable_intersection)
    {
        dist = get_sphere_distance(ray, sphere);
        if (dist < nearest->distance)
        {
            nearest->object = sphere;
            nearest->distance = dist;
            nearest->type = SPH;
        }
    }
    return nearest->distance;
}

// Check intersection with a cylinder
float check_cylinder_intersection(t_ray *ray, t_list *current, t_hit_info *nearest)
{
    t_cylinder *cylinder = (t_cylinder *)(current->content);
    float dist;

    if (cylinder->enable_intersection)
    {
        dist = get_cylinder_distance(ray, cylinder);
        if (dist < nearest->distance)
        {
            nearest->object = cylinder;
            nearest->distance = dist;
            nearest->type = CYL;
        }
    }
    return nearest->distance;
}

// Check intersection with a plane
float check_plane_intersection(t_ray *ray, t_list *current, t_hit_info *nearest)
{
    t_plane *plane = (t_plane *)(current->content);
    float dist;

    if (plane->enable_intersection)
    {
        dist = get_plane_distance(ray, plane);
        if (dist < nearest->distance)
        {
            nearest->object = plane;
            nearest->distance = dist;
            nearest->type = PLN;
        }
    }
    return nearest->distance;
}

// Check intersection with a cone
float check_cone_intersection(t_ray *ray, t_list *current, t_hit_info *nearest)
{
    t_cone *cone = (t_cone *)(current->content);
    float dist;

    if (cone->enable_intersection)
    {
        dist = get_cone_distance(ray, cone);
        if (dist < nearest->distance)
        {
            nearest->object = cone;
            nearest->distance = dist;
            nearest->type = CONE;
        }
    }
    return nearest->distance;
}

// Iterate through all spheres in the scene and check intersection
void check_spheres(t_ray *ray, t_scene *scene, t_hit_info *nearest)
{
    t_list *current = *(scene->spheres);
    while (current)
    {
        check_sphere_intersection(ray, current, nearest);
        current = current->next;
    }
}

// Iterate through all cylinders in the scene and check intersection
void check_cylinders(t_ray *ray, t_scene *scene, t_hit_info *nearest)
{
    t_list *current = *(scene->cylinders);
    while (current)
    {
        check_cylinder_intersection(ray, current, nearest);
        current = current->next;
    }
}

// Iterate through all planes in the scene and check intersection
void check_planes(t_ray *ray, t_scene *scene, t_hit_info *nearest)
{
    t_list *current = *(scene->planes);
    while (current)
    {
        check_plane_intersection(ray, current, nearest);
        current = current->next;
    }
}

// Iterate through all cones in the scene and check intersection
void check_cones(t_ray *ray, t_scene *scene, t_hit_info *nearest)
{
    t_list *current = *(scene->cones);
    while (current)
    {
        check_cone_intersection(ray, current, nearest);
        current = current->next;
    }
}

// Main function to get the nearest intersection
t_intersection *ft_get_nearest_intersection(t_ray *ray, t_scene *scene)
{
    t_hit_info nearest = {NULL, INFINITY, NONE};

    check_spheres(ray, scene, &nearest);
    check_cylinders(ray, scene, &nearest);
    check_planes(ray, scene, &nearest);
    check_cones(ray, scene, &nearest);

    if (nearest.distance == INFINITY)
        return NULL;

    return create_intersection(ray, &nearest);
}
