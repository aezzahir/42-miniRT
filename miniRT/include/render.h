#ifndef RENDER_H
#define RENDER_H

#include "miniRT.h"

/*
 * render.h
 * Declarations for rendering and raytracing functions
 */
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

void ft_setup_camera(t_camera *camera);

#endif  // RENDER_H