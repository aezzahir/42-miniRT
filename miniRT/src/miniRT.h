/**
 * @file miniRT.h
 * @brief Main header file for the miniRT project
 */

#ifndef MINIRT_H
#define MINIRT_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/vector.h"

// Color structure
typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

// Ray structure
typedef struct s_ray {
    t_vector origin;
    t_vector direction;
} t_ray;

// Ambient light structure
typedef struct s_ambient {
    double ratio;
    t_color color;
} t_ambient;

// Light structure
typedef struct s_light {
    t_vector position;
    double brightness;
    t_color color;
} t_light;

// Camera structure
typedef struct s_camera {
    t_vector position;
    t_vector orientation;
    double fov;
    double aspect_ratio;
    double viewport_height;
    double viewport_width;
    t_vector forward;
    t_vector up;
    t_vector right;
} t_camera;

// Sphere structure
typedef struct s_sphere {
    t_vector center;
    double diameter;
    t_color color;
} t_sphere;

// Intersection structure
typedef struct s_intersection {
    double t;
    t_color color;
    t_vector normal;
    t_vector point;
    void *object;
} t_intersection;

// Scene structure
typedef struct s_scene {
    t_ambient ambient;
    t_camera camera;
    t_light light;
    t_sphere sphere;
} t_scene;

// Image structure
typedef struct s_img {
    void *img_ptr;
    char *img_pixel_ptr;
    int bits_per_pixel;
    int endian;
    int line_len;
} t_img;

// MLX data structure
typedef struct s_mlx_data {
    void *mlx_connection;
    void *mlx_window;
    t_img image;
    t_scene *scene;
    int frame;
} t_mlx_data;

// Function prototypes
void ft_setup_camera(t_camera *camera);
t_intersection *intersect_sphere(t_ray *ray, t_sphere *sphere);

#endif /* MINIRT_H */