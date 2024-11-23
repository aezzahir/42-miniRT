/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:02 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 12:03:47 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "geometry.h"
# include "miniRT.h"
# include <stdbool.h>
# include "vector.h"

/*
 * render.h
 * Declarations for rendering and raytracing functions
 */

// MLX data structure
// Image structure

typedef struct s_mouse_state
{
	int				is_left_pressed;
	int				is_right_pressed;
	int				last_x;
	int				last_y;
}					t_mouse_state;

typedef struct s_img
{
	void			*img_ptr;
	char			*img_pixel_ptr;
	int				bits_per_pixel;
	int				endian;
	int				line_len;
}					t_img;

typedef struct s_mlx_data
{
	int				width;
	int				height;
	void			*mlx_connection;
	void			*mlx_window;
	t_img			image;
	t_scene			*scene;
	t_mouse_state	mouse;
	int				redraw_needed;
}					t_mlx_data;

typedef struct s_camera
{
	t_vector		position;
	t_vector		orientation;
	float			fov;
	float			aspect_ratio;
	float			viewport_height;
	float			viewport_width;
	t_vector		forward;
	t_vector		up;
	t_vector		right;
	float camera_to_world[4][4];
}					t_camera;

typedef struct s_lighting_vectors
{
    t_vector normal;
    t_vector light_dir;
    t_vector view_dir;
} t_lighting_vectors;

typedef struct s_transform
{
    t_vector    rotation;
    t_vector    translation;
    t_color     color;
    float       d_h;
}   t_transform;

typedef struct s_world_transform
{
    float       world_dx;
    float       world_dy;
    float       distance_scale;
    float       dist;
    t_vector    translation;
    t_vector    obj_pos;
} t_world_transform;

void				ft_setup_camera(t_camera *camera);
t_ray				ft_generate_ray(float x, float y, t_scene *scene);
t_color				trace_ray(t_ray *ray, t_scene *scene, int depth);
void				render_scene(t_scene *scene, t_mlx_data *data);
void				transform_scene(t_scene *scene, t_vector rotation,
						t_vector translation, t_color color);
void				ft_resize_unique_property(t_scene *scene, float d_r,
						float d_h);

// WINDOW MANAGEMENT

void				my_pixel_put(t_img *img, int x, int y, int color);
int					expose_hook(t_mlx_data *data);
int					key_hook(int keycode, t_mlx_data *data);
int					key_press(int keycode, t_mlx_data *data);
int					handle_user_input(int key, t_scene *scene);
int					mouse_hook(int button, int x, int y, t_mlx_data *data);
int					loop_hook(t_mlx_data *data);
int					ft_close(t_mlx_data *data);

// --- transformation using the mouse
int					mouse_release(int button, int x, int y, t_mlx_data *data);
int					mouse_move(int x, int y, t_mlx_data *data);

t_color	handle_no_intersection(t_scene *scene);
t_lighting_vectors	calculate_vectors(t_scene *scene,
		t_intersection *intersection, t_ray *ray);

t_vector	get_normal(void *object, t_vector point, int type);


#endif // RENDER_H