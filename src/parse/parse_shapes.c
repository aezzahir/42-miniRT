/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:10:48 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 16:02:32 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static int	ft_free(void *shape, char **s)
{
	free(shape);
	ft_free_split(s);
	return (0);
}

int	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*sphere;
	char		**parts;

	sphere = malloc(sizeof(t_sphere));
	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2] || !parts[3] || parts[4])
		return (ft_free(sphere, parts));
	if (!parse_vector(parts[1], &sphere->center))
		return (ft_free(sphere, parts));
	sphere->diameter = ft_atof(parts[2]);
	if (sphere->diameter <= 0 || !parse_color(parts[3], &sphere->color))
		return (ft_free(sphere, parts));
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
		return (ft_free(cylinder, parts));
	if (!parse_vector(parts[1], &cylinder->center) || !parse_vector(parts[2],
			&cylinder->axis))
		return (ft_free(cylinder, parts));
	cylinder->diameter = ft_atof(parts[3]);
	cylinder->height = ft_atof(parts[4]);
	if (cylinder->diameter <= 0 || cylinder->height <= 0
		|| !parse_color(parts[5], &cylinder->color))
		return (ft_free(cylinder, parts));
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
		return (ft_free(cone, parts));
	if (!parse_vector(parts[1], &cone->center) || !parse_vector(parts[2],
			&cone->axis))
		return (ft_free(cone, parts));
	cone->diameter = ft_atof(parts[3]);
	cone->height = ft_atof(parts[4]);
	if (cone->diameter <= 0 || cone->height <= 0 || !parse_color(parts[5],
			&cone->color))
		return (ft_free(cone, parts));
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
		return (ft_free(plane, parts));
	if (!parse_vector(parts[1], &plane->point) || !parse_vector(parts[2],
			&plane->normal))
		return (ft_free(plane, parts));
	if (!parse_color(parts[3], &plane->color))
		return (ft_free(plane, parts));
	ft_lstadd_back(scene->planes, ft_lstnew(plane));
	ft_free_split(parts);
	plane->enable_intersection = 1;
	return (1);
}
