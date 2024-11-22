/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:12:50 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 05:31:23 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vector1.c
 * @brief Defines vector operations
 */

#include "../../include/miniRT.h"

float	vector_magnitude(t_vector v)
{
	return (sqrt(vector_dot_product(v, v)));
}

t_vector	vector_normalize(t_vector v)
{
	float	mag;

	mag = vector_magnitude(v);
	if (mag == 0.0)
		return (v);
	return (vector_create(v.x / mag, v.y / mag, v.z / mag));
}

t_vector	vector_multiply(t_vector v, float scalar)
{
	return (vector_create(v.x * scalar, v.y * scalar, v.z * scalar));
}

float	vector_distance(t_vector v1, t_vector v2)
{
	return (vector_magnitude(vector_subtract(v2, v1)));
}

t_vector	vector_negate(t_vector v)
{
	return (vector_create(-v.x, -v.y, -v.z));
}
