
#include "../include/miniRT.h"


void free_sphere(void *content)
{
    t_sphere *sphere = (t_sphere *)content;
    if (sphere)
        free(sphere);
}

void free_plane(void *content)
{
    t_plane *plane = (t_plane *)content;
    if (plane)
        free(plane);
}

void free_cylinder(void *content)
{
    t_cylinder *cylinder = (t_cylinder *)content;
    if (cylinder)
        free(cylinder);
}

void free_cone(void *content)
{
    t_cone *cone = (t_cone *)content;
    if (cone)
        free(cone);
}

// Main scene cleanup function
void clear_scene(t_scene *scene)
{
    if (!scene)
        return;

    // Clear spheres list
    if (scene->spheres)
    {
        ft_lstclear(scene->spheres, free_sphere);
        free(scene->spheres);
        scene->spheres = NULL;
    }

    // Clear planes list
    if (scene->planes)
    {
        ft_lstclear(scene->planes, free_plane);
        free(scene->planes);
        scene->planes = NULL;
    }

    // Clear cylinders list
    if (scene->cylinders)
    {
        ft_lstclear(scene->cylinders, free_cylinder);
        free(scene->cylinders);
        scene->cylinders = NULL;
    }

    // Clear cones list
    if (scene->cones)
    {
        ft_lstclear(scene->cones, free_cone);
        free(scene->cones);
        scene->cones = NULL;
    }

    // Reset scene parameters
    scene->camera.position = (t_vector){0, 0, 0};
    scene->camera.orientation = (t_vector){0, 0, 0};
    scene->camera.fov = 0;
    scene->light.position = (t_vector){0, 0, 0};
    scene->light.brightness = 0;
    scene->light.color = (t_color){0, 0, 0};
    scene->ambient.ratio = 0;
    scene->ambient.color = (t_color){0, 0, 0};
}

// Optional: Function to reinitialize scene after clearing
void reset_scene(t_scene *scene)
{
    clear_scene(scene);

    // Reinitialize scene pointers
    scene->spheres = malloc(sizeof(t_list *));
    scene->planes = malloc(sizeof(t_list *));
    scene->cylinders = malloc(sizeof(t_list *));
    scene->cones = malloc(sizeof(t_list *));

    if (scene->spheres) *(scene->spheres) = NULL;
    if (scene->planes) *(scene->planes) = NULL;
    if (scene->cylinders) *(scene->cylinders) = NULL;
    if (scene->cones) *(scene->cones) = NULL;

    // Set default values
    scene->camera.position = (t_vector){0, 0, 0};
    scene->camera.orientation = (t_vector){0, 0, 1};
    scene->camera.fov = 60;
    scene->light.position = (t_vector){0, 0, 0};
    scene->light.brightness = 1.0;
    scene->light.color = (t_color){255, 255, 255};
    scene->ambient.ratio = 0.1;
    scene->ambient.color = (t_color){255, 255, 255};
}

// Error checking wrapper for scene initialization
bool init_scene(t_scene *scene)
{
    scene->spheres = malloc(sizeof(t_list *));
    if (!scene->spheres)
        return false;

    scene->planes = malloc(sizeof(t_list *));
    if (!scene->planes)
    {
        free(scene->spheres);
        return false;
    }

    scene->cylinders = malloc(sizeof(t_list *));
    if (!scene->cylinders)
    {
        free(scene->spheres);
        free(scene->planes);
        return false;
    }

    scene->cones = malloc(sizeof(t_list *));
    if (!scene->cones)
    {
        free(scene->spheres);
        free(scene->planes);
        free(scene->cylinders);
        return false;
    }

    *(scene->spheres) = NULL;
    *(scene->planes) = NULL;
    *(scene->cylinders) = NULL;
    *(scene->cones) = NULL;

    return true;
}
