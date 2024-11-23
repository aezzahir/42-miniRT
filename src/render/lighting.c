/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:06 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 11:51:37 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * lighting.c
 * Implements lighting calculations
 * Manages ambient, diffuse, and shadow computations
 */
#include "../../include/miniRT.h"

t_color	calculate_ambient(t_scene *scene, t_color object_color)
{
	return (color_multiply(color_scale(scene->ambient.color,
				scene->ambient.ratio), object_color));
}

t_color	calculate_diffuse(t_scene *scene, t_vector normal, t_vector light_dir,
		t_color object_color)
{
	float	diff;

	diff = fmaxf(vector_dot_product(normal, light_dir), 0.0);
	return (color_multiply(color_scale(scene->light.color, diff
				* scene->light.brightness), object_color));
}

t_color	calculate_specular(t_scene *scene, t_vector normal, t_vector light_dir,
		t_vector view_dir)
{
	t_specular_data	s;

	s.ks = 0.8;
	s.shininess = 32.0;
	s.reflect_dir = vector_reflect(vector_negate(light_dir), normal);
	s.cos_alpha = fmaxf(vector_dot_product(view_dir, s.reflect_dir), 0.0);
	s.spec = s.ks * powf(s.cos_alpha, s.shininess);
	s.intensity = s.spec * scene->light.brightness;
	return (color_scale(scene->light.color, s.intensity));
}

float	calculate_shadow(t_scene *scene, t_point hit_point, t_vector light_dir)
{
	float			light_distance;
	t_intersection	*shadow_intersection;
	t_ray			shadow_ray;

	light_distance = vector_length(vector_subtract(scene->light.position,
				hit_point));
	shadow_ray.origin = hit_point;
	shadow_ray.direction = light_dir;
	shadow_intersection = ft_get_nearest_intersection(&shadow_ray, scene);
	if (shadow_intersection && shadow_intersection->t < 0.99 * light_distance)
	{
		free(shadow_intersection);
		return (0.0);
	}
	if (shadow_intersection)
	{
		free(shadow_intersection);
	}
	return (1.0);
}
