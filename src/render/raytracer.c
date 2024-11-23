/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:11 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 09:42:14 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * raytracer.c
 * Core raytracing logic
 * Implements the main raytracing algorithm
 */
#include "../../include/miniRT.h"

float	get_object_distance(t_ray *ray, void *object, t_object_type type)
{
	if (type == SPH)
		return (get_sphere_distance(ray, (t_sphere *)object));
	if (type == CYL)
		return (get_cylinder_distance(ray, (t_cylinder *)object));
	if (type == PLN)
		return (get_plane_distance(ray, (t_plane *)object));
	if (type == CONE)
		return (get_cone_distance(ray, (t_cone *)object));
	return (INFINITY);
}

static t_vector	get_normal(void *object, t_vector point, int type)
{
	if (type == SPH)
		return (vector_normalize(vector_subtract(point,
					((t_sphere *)object)->center)));
	if (type == CYL)
		return (calculate_cylinder_normal(object, point));
	if (type == PLN)
		return (((t_plane *)object)->normal);
	if (type == CONE)
		return (calculate_cone_normal(object, point));
	return ((t_vector){0, 0, 0});
}

t_intersection	*create_intersection(t_ray *ray, t_hit_info *hit)
{
	t_intersection	*inter;

	inter = malloc(sizeof(t_intersection));
	if (!inter)
		return (NULL);
	inter->t = hit->distance;
	inter->point = vector_add(ray->origin, vector_multiply(ray->direction,
				hit->distance));
	inter->object = hit->object;
	inter->object_type = hit->type;
	if (hit->type == SPH)
		inter->color = ((t_sphere *)hit->object)->color;
	else if (hit->type == CYL)
		inter->color = ((t_cylinder *)hit->object)->color;
	else if (hit->type == PLN)
		inter->color = ((t_plane *)hit->object)->color;
	else if (hit->type == CONE)
		inter->color = ((t_cone *)hit->object)->color;
	inter->normal = get_normal(hit->object, inter->point, hit->type);
	return (inter);
}

t_vector	ft_get_surface_normal_vector(t_intersection *inter)
{
	t_vector	normal;

	normal = {0, 0, 0};
	if (!inter)
		return (normal);
	if (inter->object_type == SPH)
		normal = vector_normalize(vector_subtract(inter->point,
					((t_sphere *)inter->object)->center));
	else if (inter->object_type == CYL)
		normal = calculate_cylinder_normal((t_cylinder *)inter->object,
				inter->point);
	else if (inter->object_type == PLN)
		normal = ((t_plane *)inter->object)->normal;
	else if (inter->object_type == CONE)
		normal = calculate_cone_normal((t_cone *)inter->object, inter->point);
	return (normal);
}

void	ft_enable_intersecton(t_intersection *inter, int value)
{
	if (!inter)
		return ;
	if (inter->object_type == SPH)
		((t_sphere *)inter->object)->enable_intersection = value;
	else if (inter->object_type == CYL)
		((t_cylinder *)inter->object)->enable_intersection = value;
	else if (inter->object_type == PLN)
		((t_plane *)inter->object)->enable_intersection = value;
	else if (inter->object_type == CONE)
		((t_cone *)inter->object)->enable_intersection = value;
}

void	render_scene(t_scene *scene, t_mlx_data *data)
{
	t_color	anti_aliased_color;
	int		y;
	int		x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			anti_aliased_color = anti_alias_pixel(scene, x, y);
			my_pixel_put(&(data->image), x, y,
				color_to_int(anti_aliased_color));
			x++;
		}
		y++;
	}
}
