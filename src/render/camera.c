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

void	ft_setup_camera(t_camera *camera)
{
	camera->forward = vector_normalize(camera->orientation);
	camera->right = vector_cross_product(camera->forward, (t_vector){0, 1, 0});
	camera->up = vector_cross_product(camera->right, camera->forward);
	camera->aspect_ratio = (float)WIDTH / HEIGHT;
	camera->viewport_height = 2 * tan((camera->fov * PI / 180) / 2);
	camera->viewport_width = camera->aspect_ratio * camera->viewport_height;
}
