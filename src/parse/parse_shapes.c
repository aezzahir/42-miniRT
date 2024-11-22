/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:10:48 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 09:10:49 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*sphere;
	char		**parts;

	sphere = malloc(sizeof(t_sphere));
	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2] || !parts[3] || parts[4])
	{
		free(sphere);
		ft_free_split(parts);
		return (0);
	}
	if (!parse_vector(parts[1], &sphere->center))
	{
		free(sphere);
		ft_free_split(parts);
		return (0);
	}
	sphere->diameter = ft_atof(parts[2]);
	if (sphere->diameter <= 0 || !parse_color(parts[3], &sphere->color))
	{
		free(sphere);
		ft_free_split(parts);
		return (0);
	}
	ft_lstadd_back(scene->spheres, ft_lstnew(sphere));
	ft_free_split(parts);
	sphere->enable_intersection = 1;
	return (1);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cylinder;
	char		**parts;

	cylinder = malloc(sizeof(t_cylinder));
	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2] || !parts[3] || !parts[4] || !parts[5]
		|| parts[6])
	{
		free(cylinder);
		ft_free_split(parts);
		return (0);
	}
	if (!parse_vector(parts[1], &cylinder->center) || !parse_vector(parts[2],
			&cylinder->axis))
	{
		free(cylinder);
		ft_free_split(parts);
		return (0);
	}
	cylinder->diameter = ft_atof(parts[3]);
	cylinder->height = ft_atof(parts[4]);
	if (cylinder->diameter <= 0 || cylinder->height <= 0
		|| !parse_color(parts[5], &cylinder->color))
	{
		free(cylinder);
		ft_free_split(parts);
		return (0);
	}
	ft_lstadd_back(scene->cylinders, ft_lstnew(cylinder));
	ft_free_split(parts);
	cylinder->enable_intersection = 1;
	return (1);
}

int	parse_cone(char *line, t_scene *scene)
{
	t_cone	*cone;
	char	**parts;

	cone = malloc(sizeof(t_cone));
	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2] || !parts[3] || !parts[4] || !parts[5]
		|| parts[6])
	{
		free(cone);
		ft_free_split(parts);
		return (0);
	}
	if (!parse_vector(parts[1], &cone->center) || !parse_vector(parts[2],
			&cone->axis))
	{
		free(cone);
		ft_free_split(parts);
		return (0);
	}
	cone->diameter = ft_atof(parts[3]);
	cone->height = ft_atof(parts[4]);
	if (cone->diameter <= 0 || cone->height <= 0 || !parse_color(parts[5],
			&cone->color))
	{
		free(cone);
		ft_free_split(parts);
		return (0);
	}
	ft_lstadd_back(scene->cones, ft_lstnew(cone));
	ft_free_split(parts);
	cone->enable_intersection = 1;
	return (1);
}

int	parse_plane(char *line, t_scene *scene)
{
	t_plane	*plane;
	char	**parts;

	plane = malloc(sizeof(t_plane));
	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2] || !parts[3] || parts[4])
	{
		free(plane);
		ft_free_split(parts);
		return (0);
	}
	if (!parse_vector(parts[1], &plane->point) || !parse_vector(parts[2],
			&plane->normal))
	{
		free(plane);
		ft_free_split(parts);
		return (0);
	}
	if (!parse_color(parts[3], &plane->color))
	{
		free(plane);
		ft_free_split(parts);
		return (0);
	}
	ft_lstadd_back(scene->planes, ft_lstnew(plane));
	ft_free_split(parts);
	plane->enable_intersection = 1;
	return (1);
}
