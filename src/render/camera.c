/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:12:59 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/20 22:13:00 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * camera.c
 * Defines camera properties and operations
 * Handles ray generation from camera viewpoint
 */
#include "../../include/miniRT.h"
#include <math.h>
#define PI 3.14159265359
#include "../../include/miniRT.h"

void camera_to_world_matrix(t_camera *camera, float m[4][4])
{
    t_vector forward = camera->forward;
    t_vector right = camera->right;
    t_vector up = camera->up;
    t_point position = camera->position;

    m[0][0] = right.x;
    m[0][1] = right.y;
    m[0][2] = right.z;
    m[0][3] = -vector_dot_product(right, position);

    m[1][0] = up.x;
    m[1][1] = up.y;
    m[1][2] = up.z;
    m[1][3] = -vector_dot_product(up, position);

    m[2][0] = -forward.x;
    m[2][1] = -forward.y;
    m[2][2] = -forward.z;
    m[2][3] = vector_dot_product(forward, position);

    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;
}
void	ft_setup_camera(t_camera *camera)
{
	camera->forward = vector_normalize(camera->orientation);
	camera->right = vector_cross_product(camera->forward, (t_vector){0, 1, 0});
	camera->up = vector_cross_product(camera->right, camera->forward);
	camera->aspect_ratio = (float)WIDTH / HEIGHT;
	camera->viewport_height = 2 * tan((camera->fov * PI / 180) / 2);
	camera->viewport_width = camera->aspect_ratio * camera->viewport_height;
	camera_to_world_matrix(camera, camera->camera_to_world);

}
