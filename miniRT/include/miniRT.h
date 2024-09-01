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
#include "vector.h"
#include "render.h"
#include "parser.h"
#include "geometry.h"
#include "utils.h"
#include "color.h"

#define WIDTH 800
#define HEIGHT 600
#define MAX_DEPTH 100
// Color structure

typedef t_vector t_point; // the point and vector have the same representation but different meaning a point is as specific location in the 3D space P(x, y, z)
                            // but a vector is not he indicate a direction and a magnitude V(x, y, z)


// Ray structure
typedef struct s_ray {
    t_point origin;  // origin of ray is a point on the 3D space
    t_vector direction; // direction of ray is   a vector on the 3D space
} t_ray;

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

// Sphere structure
typedef struct s_sphere {
    t_vector center;
    float diameter;
    t_color color;
} t_sphere;

// Intersection structure
typedef struct s_intersection {
    float t;
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