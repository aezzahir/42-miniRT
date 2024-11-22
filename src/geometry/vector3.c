/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:12:50 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 06:33:07 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vector3.c
 * @brief Defines vector operations
 */

#include "../../include/miniRT.h"

t_vector	vector_rotate_x(t_vector v, float angle)
{
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	return (vector_create(v.x, v.y * cos_a - v.z * sin_a, v.y * sin_a + v.z
			* cos_a));
}

t_vector	vector_rotate_y(t_vector v, float angle)
{
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	return (vector_create(v.x * cos_a + v.z * sin_a, v.y, -v.x * sin_a + v.z
			* cos_a));
}

t_vector	vector_rotate_z(t_vector v, float angle)
{
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	return (vector_create(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a,
			v.z));
}

t_vector	vector_rotate(t_vector v, t_vector rotation)
{
	v = vector_rotate_x(v, rotation.x);
	v = vector_rotate_y(v, rotation.y);
	v = vector_rotate_z(v, rotation.z);
	return (v);
}
