/*
 * camera.c
 * Defines camera properties and operations
 * Handles ray generation from camera viewpoint
 */
#include "../../include/miniRT.h"
#include <math.h>

void ft_setup_camera(t_camera *camera) {
    camera->forward = vector_normalize(camera->orientation);
    camera->right = vector_cross_product(camera->forward, (t_vector){0, 1, 0});
    camera->up = vector_cross_product(camera->right, camera->forward);

    camera->aspect_ratio = (float)WIDTH / HEIGHT;
    camera->viewport_height = 2 * tan((camera->fov * M_PI / 180) / 2);
    camera->viewport_width = camera->aspect_ratio * camera->viewport_height;
}