/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:12:50 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 09:10:29 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vector2.c
 * @brief Defines vector operations
 */

#include "../../include/miniRT.h"

t_vector	vector_reflect(t_vector incident, t_vector normal)
{
	float		dot;
	t_vector	scaled_normal;

	dot = vector_dot_product(incident, normal);
	scaled_normal = vector_multiply(normal, 2 * dot);
	return (vector_subtract(incident, scaled_normal));
}

float	vector_length(t_vector v)
{
	return (vector_magnitude(v));
}

void	vector_print(t_vector v)
{
	printf("Vector: (%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}

t_vector	vector_translate(t_vector v, t_vector translation)
{
	return (vector_add(v, translation));
}
