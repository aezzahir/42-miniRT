/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:02 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 08:03:30 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
#define RENDER_H


#include "geometry.h"
#include "miniRT.h"

/*
 * render.h
 * Declarations for rendering and raytracing functions
 */

// MLX data structure
// Image structure

typedef struct s_mouse_state {
    int is_left_pressed;
    int is_right_pressed;
    int last_x;
    int last_y;
} t_mouse_state;

typedef struct s_img {
    void *img_ptr;
    char *img_pixel_ptr;
    int bits_per_pixel;
    int endian;
    int line_len;
} t_img;

typedef struct s_mlx_data {
    int width;
    int height;
    void *mlx_connection;
    void *mlx_window;
    t_img image;
    t_scene *scene;
    t_mouse_state mouse;
    int redraw_needed;
} t_mlx_data;



typedef struct s_camera {
    t_vector position;
    t_vector orientation;
    float fov;
    float aspect_ratio;
    float viewport_height;
    float viewport_width;
    t_vector forward;
    t_vector up;
    t_vector right;
} t_camera;

void ft_setup_camera(t_camera *camera);
t_ray ft_generate_ray(float x, float y, t_scene *scene);
t_color trace_ray(t_ray *ray, t_scene *scene, int depth);
void render_scene(t_scene *scene, t_mlx_data *data);
bool is_in_shadow(t_ray *shadow_ray, t_scene *scene, float light_distance);
void transform_scene(t_scene *scene, t_vector rotation, t_vector translation, t_color color);
void ft_resize_unique_property(t_scene *scene, float d_r, float d_h);




// WINDOW MANAGEMENT 

void my_pixel_put(t_img *img, int x, int y, int color);
int expose_hook(t_mlx_data *data);
int key_hook(int keycode, t_mlx_data *data);
int key_press(int keycode, t_mlx_data *data);
int handle_user_input(int key, t_scene *scene);
int mouse_hook(int button, int x, int y, t_mlx_data *data);
int loop_hook(t_mlx_data *data);
int ft_close(t_mlx_data *data);




// --- transformation using the mouse 
int mouse_press(int button, int x, int y, t_mlx_data *data);
int mouse_release(int button, int x, int y, t_mlx_data *data);
int mouse_move(int x, int y, t_mlx_data *data);


#endif  // RENDER_H