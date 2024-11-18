/**
 * @file miniRT.h
 * @brief Main header file for the miniRT project
 */

#ifndef MINIRT_H
#define MINIRT_H

#include <mlx.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../lib/libft/libft.h"
#include "vector.h"
#include "color.h"
#include "render.h"
#include "parser.h"
#include "geometry.h"
#include "utils.h"
#include "scene_cleanup.h"

#define WIDTH 920
#define HEIGHT 600
#define MAX_DEPTH 100
// Color structure


// Ray structure
typedef struct s_object {
    t_object_type type;
    void *shape;
    //t_material material;
} t_object;
// Scene structure
typedef struct s_hit_info {
    void        *object;
    float       distance;
    t_object_type type;
} t_hit_info;
// Ambient light structure
typedef struct s_ambient {
    float ratio;  // ratio of   diffuse light to ambient light
    t_color color;
} t_ambient;

// Light structure
typedef struct s_light {
    t_vector position;
    float brightness;
    t_color color;
} t_light;

// Camera structure






typedef struct s_scene {
    t_object  selected_object;
    t_ambient ambient;
    t_camera camera;
    t_light light;
    t_list **spheres;
    t_list **planes;
    t_list **cylinders;
    t_list **cones;
} t_scene;





// Function prototypes
int parse_scene(char *filename, t_scene *scene);
int mlx_data_init(t_mlx_data *data);
void ft_scene_init(t_scene *scene);
void render_scene(t_scene *scene, t_mlx_data *data);
void render_scene_with_aa(t_scene *scene, t_mlx_data *data);


t_color calculate_ambient(t_scene *scene, t_color object_color);
t_color calculate_diffuse(t_scene *scene, t_vector normal, t_vector light_dir, t_color object_color);
t_color calculate_specular(t_scene *scene, t_vector normal, t_vector light_dir, t_vector view_dir);
float calculate_shadow(t_scene *scene, t_point hit_point, t_vector light_dir);
t_color calculate_reflection(t_ray *ray, t_intersection *intersection, t_scene *scene, int depth);
t_color calculate_refraction(t_ray *ray, t_intersection *intersection, t_scene *scene, int depth);
int vector_refract(t_vector incident, t_vector normal, float eta, t_vector *refracted);


t_intersection *create_intersection(t_ray *ray, t_hit_info *hit);
#endif /* MINIRT_H */