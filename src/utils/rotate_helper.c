/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:17:48 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 11:19:15 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_vector	rotate_x(t_vector v, float angle)
{
	float	cos_a;
	float	sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	return ((t_vector){v.x, v.y * cos_a - v.z * sin_a, v.y * sin_a + v.z
		* cos_a});
}

t_vector	rotate_y(t_vector v, float angle)
{
	float	cos_a;
	float	sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	return ((t_vector){v.x * cos_a + v.z * sin_a, v.y, -v.x * sin_a + v.z
		* cos_a});
}

t_vector	rotate_z(t_vector v, float angle)
{
	float	cos_a;
	float	sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	return ((t_vector){v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a,
		v.z});
}
