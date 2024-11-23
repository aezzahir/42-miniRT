/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:07:49 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 22:23:00 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_quadratic_params
{
    float a;
    float b;
    float c;
    float discriminant;
} t_quadratic_params;


// parsing
int parse_scene(char *filename, t_scene *scene);
bool	init_scene(t_scene *scene);
double ft_atof(const char *str);
char	*get_next_line(int fd);
int parse_ambient(char *line, t_scene *scene);
int parse_light(char *line, t_scene *scene);
int parse_sphere(char *line, t_scene *scene);
int parse_cylinder(char *line, t_scene *scene);
int parse_cone(char *line, t_scene *scene);
int parse_plane(char *line, t_scene *scene);
int parse_color(char *str, t_color *color);
void	ft_free_split(char **str);
int parse_vector(char *str, t_vector *vec);

// Function prototypes
int mlx_data_init(t_mlx_data *data);
void ft_scene_init(t_scene *scene);
void render_scene(t_scene *scene, t_mlx_data *data);
void render_scene_with_aa(t_scene *scene, t_mlx_data *data);


t_color calculate_ambient(t_scene *scene, t_color object_color);
t_color calculate_diffuse(t_scene *scene, t_vector normal, t_vector light_dir, t_color object_color);
t_color calculate_specular(t_scene *scene, t_vector normal, t_vector light_dir, t_vector view_dir);
float calculate_shadow(t_scene *scene, t_point hit_point, t_vector light_dir);



// rotate
t_vector rotate_x(t_vector v, float angle);
t_vector rotate_y(t_vector v, float angle);
t_vector rotate_z(t_vector v, float angle);
void object_rotate(t_object *o, t_vector r);
void camera_rotate(t_camera *camera, t_vector rotation);

t_color anti_alias_pixel(t_scene *scene, int x, int y);

t_vector ft_get_surface_normal_vector(t_intersection *inter);
t_ray ft_generate_ray(float x, float y, t_scene *scene);
void ft_enable_intersecton(t_intersection *inter, int value);

t_intersection *create_intersection(t_ray *ray, t_hit_info *hit);

t_vector	get_world_space_translation(t_mlx_data *data, t_camera *camera,
		int dx, int dy);
#endif /* MINIRT_H */