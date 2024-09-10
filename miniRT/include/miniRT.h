/**
 * @file miniRT.h
 * @brief Main header file for the miniRT project
 */

#ifndef MINIRT_H
#define MINIRT_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../lib/libft/libft.h"
#include "color.h"
#include "vector.h"
#include "render.h"
#include "parser.h"
#include "geometry.h"
#include "utils.h"


#define WIDTH 800
#define HEIGHT 600
#define MAX_DEPTH 100
// Color structure


// Ray structure


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




// Scene structure
typedef struct s_scene {
    t_ambient ambient;
    t_camera camera;
    t_light light;
    t_list **spheres;
    t_list **planes;
    t_list **cylinders;
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
int parse_scene(char *filename, t_scene *scene);
int mlx_data_init(t_mlx_data *data);
void ft_scene_init(t_scene *scene);
void render_scene(t_scene *scene, t_mlx_data *data);
#endif /* MINIRT_H */