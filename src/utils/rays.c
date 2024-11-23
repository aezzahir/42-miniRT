/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:31 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 11:24:53 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static t_color	handle_no_intersection(t_scene *scene)
{
	return (color_scale(scene->ambient.color, scene->ambient.ratio));
}

// Helper function to calculate lighting vectors
static t_lighting_vectors calculate_vectors(t_scene *scene, 
    t_intersection *intersection, t_ray *ray)
{
    t_lighting_vectors vectors;
    
    vectors.normal = ft_get_surface_normal_vector(intersection);
    vectors.light_dir = vector_normalize(vector_subtract(scene->light.position,
        intersection->point));
    vectors.view_dir = vector_normalize(vector_negate(ray->direction));
    
    return (vectors);
}

// Helper function to calculate colors
static t_color calculate_colors(t_scene *scene, t_intersection *intersection,
    t_lighting_vectors vectors)
{
    t_color ambient;
    t_color diffuse;
    t_color specular;
    float shadow_factor;
    
    ambient = calculate_ambient(scene, intersection->color);
    diffuse = calculate_diffuse(scene, vectors.normal, vectors.light_dir,
        intersection->color);
    specular = calculate_specular(scene, vectors.normal, vectors.light_dir,
        vectors.view_dir);
    shadow_factor = calculate_shadow(scene, intersection->point,
        vectors.light_dir);
    
    return (color_add(ambient, color_scale(color_add(diffuse, specular),
        shadow_factor)));
}

// Main lighting computation function
static t_color compute_lighting(t_scene *scene, t_intersection *intersection,
    t_ray *ray)
{
    t_lighting_vectors vectors;
    t_color local_color;
    
    vectors = calculate_vectors(scene, intersection, ray);
    local_color = calculate_colors(scene, intersection, vectors);
    
    return (local_color);
}

t_color	trace_ray(t_ray *ray, t_scene *scene, int depth)
{
	t_intersection	*intersection;
	t_color			local_color;

	if (depth <= 0)
		return (scene->ambient.color);
	intersection = ft_get_nearest_intersection(ray, scene);
	if (!intersection)
		return (handle_no_intersection(scene));
	ft_enable_intersecton(intersection, 0);
	local_color = compute_lighting(scene, intersection, ray);
	ft_enable_intersecton(intersection, 1);
	free(intersection);
	return (local_color);
}

t_ray	ft_generate_ray(float x, float y, t_scene *scene)
{
	float		pixel_x;
	float		pixel_y;
	t_vector	direction;
	t_vector	origin;

	pixel_x = (2.0 * x / WIDTH - 1) * scene->camera.viewport_width / 2;
	pixel_y = (1 - 2.0 * y / HEIGHT) * scene->camera.viewport_height / 2;
	direction = vector_normalize(vector_add(vector_add(vector_multiply(scene->camera.right,
						pixel_x), vector_multiply(scene->camera.up, pixel_y)),
				scene->camera.forward));
	origin = vector_add(scene->camera.position,
			vector_multiply(scene->camera.forward, 0.0001));
	return ((t_ray){origin, direction});
}
