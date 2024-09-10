/*
 * scene_parser.c
 * Functions to parse the .rt scene description files
 * Reads and interprets scene elements (objects, lights, camera)
 */
#include "../../include/miniRT.h"

void ft_scene_init(t_scene *scene) {
    // Ambient light and main light source
    scene->ambient = (t_ambient){0.1, (t_color){255, 255, 255}};
    scene->light = (t_light){{0, 60, -30}, 0.7, (t_color){255, 255, 255}};

    // Camera setup
    scene->camera.position = (t_point){0, 40, 80};
    scene->camera.orientation = vector_normalize((t_vector){0, -0.3, -1});
    scene->camera.fov = 90;  // Wider field of view

    // Spheres
    scene->spheres = malloc(sizeof(t_list *));
    *(scene->spheres) = NULL;
    ft_lstadd_back(scene->spheres, ft_lstnew(create_sphere((t_point){-20, 0, 0}, 10, (t_color){255, 0, 0})));     // Red sphere
    ft_lstadd_back(scene->spheres, ft_lstnew(create_sphere((t_point){0, 0, 0}, 10, (t_color){0, 255, 0})));       // Green sphere
    ft_lstadd_back(scene->spheres, ft_lstnew(create_sphere((t_point){20, 0, 0}, 10, (t_color){0, 0, 255})));      // Blue sphere

    // Cylinders
    scene->cylinders = malloc(sizeof(t_list *));
    *(scene->cylinders) = NULL;
    ft_lstadd_back(scene->cylinders, ft_lstnew(create_cylinder((t_point){-30, 0, -20}, (t_vector){2, 1, 0}, 18, 30, (t_color){255, 255, 0})));    // Yellow cylinder (vertical)
    ft_lstadd_back(scene->cylinders, ft_lstnew(create_cylinder((t_point){-10, 0, -20}, (t_vector){1, 0, 0}, 18, 30, (t_color){255, 0, 255})));    // Magenta cylinder (horizontal)
    ft_lstadd_back(scene->cylinders, ft_lstnew(create_cylinder((t_point){10, 0, -20}, (t_vector){0, 3, 1}, 15, 30, (t_color){0, 255, 255})));     // Cyan cylinder (depth-oriented)
    ft_lstadd_back(scene->cylinders, ft_lstnew(create_cylinder((t_point){30, 0, -20}, (t_vector){1, 1, 1}, 18, 30, (t_color){128, 128, 128})));   // Gray cylinder (diagonal)

    // Planes
    scene->planes = malloc(sizeof(t_list *));
    *(scene->planes) = NULL;
    ft_lstadd_back(scene->planes, ft_lstnew(create_plane((t_point){0, -10, 0}, (t_vector){0, 1, 0}, (t_color){200, 200, 200})));  // Ground plane
    ft_lstadd_back(scene->planes, ft_lstnew(create_plane((t_point){0, 0, -50}, (t_vector){0, 0, 1}, (t_color){150, 150, 200})));  // Back plane
    ft_lstadd_back(scene->planes, ft_lstnew(create_plane((t_point){-50, 0, 0}, (t_vector){1, 0, 0}, (t_color){200, 150, 150})));  // Left plane
}