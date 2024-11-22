#include "../../include/miniRT.h"

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

