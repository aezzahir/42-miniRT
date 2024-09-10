#ifndef RENDER_H
#define RENDER_H


#include "geometry.h"
#include "miniRT.h"

/*
 * render.h
 * Declarations for rendering and raytracing functions
 */
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
t_ray ft_generate_ray(int x, int y, t_scene *scene);
t_color trace_ray(t_ray *ray, t_scene *scene, int depth);
#endif  // RENDER_H