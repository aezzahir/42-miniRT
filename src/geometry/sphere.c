/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:12:47 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 05:23:23 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file sphere.c
 * @brief Implements sphere intersection calculations
 */

#include "../../include/miniRT.h"

void	ft_print_sphere(void *content)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)content;
	printf("Sphere:  center (%2f, %2f, %2f) \n", sphere->center.x,
		sphere->center.y, sphere->center.z);
}

t_sphere	*create_sphere(t_point origin, float diameter, t_color color)
{
	t_sphere	*sphere;

	sphere = NULL;
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
	{
		printf("malloc error in create_sphere\n");
		return (NULL);
	}
	sphere->center.x = origin.x;
	sphere->center.y = origin.y;
	sphere->center.z = origin.z;
	sphere->diameter = diameter;
	sphere->color.r = color.r;
	sphere->color.g = color.g;
	sphere->color.b = color.b;
	return (sphere);
}

// Distance calculation functions that only return the t value
float	get_sphere_distance(t_ray *ray, t_sphere *sphere)
{
	t_vector oc = vector_subtract(ray->origin, sphere->center);
	float a = vector_dot_product(ray->direction, ray->direction);
	float b = 2.0 * vector_dot_product(oc, ray->direction);
	float c = vector_dot_product(oc, oc) - (sphere->diameter * sphere->diameter
			/ 4.0);
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (INFINITY);

	float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	float t2 = (-b + sqrt(discriminant)) / (2.0 * a);

	// Return the nearest positive intersection
	if (t1 > 0)
		return (t1);
	if (t2 > 0)
		return (t2);
	return (INFINITY);
}