/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:12:50 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 05:27:35 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vector.c
 * @brief Defines vector operations
 */

#include "../../include/miniRT.h"

t_vector	vector_create(float x, float y, float z)
{
	return ((t_vector){x, y, z});
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	return (vector_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector	vector_subtract(t_vector v1, t_vector v2)
{
	return (vector_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

float	vector_dot_product(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector	vector_cross_product(t_vector v1, t_vector v2)
{
	return (vector_create((v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x
				* v2.z), (v1.x * v2.y) - (v1.y * v2.x)));
}
