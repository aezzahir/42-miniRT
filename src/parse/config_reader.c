/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:12:55 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 07:07:49 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/miniRT.h"
#include <fcntl.h>
#include <unistd.h>


void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
		free(str);
	str = NULL;
}

int parse_color(char *str, t_color *color)
{
    char **parts = ft_split(str, ',');
    if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
    {
        ft_free_split(parts);
        return (0);
    }
    color->r = ft_atoi(parts[0]);
    color->g = ft_atoi(parts[1]);
    color->b = ft_atoi(parts[2]);
    ft_free_split(parts);
    if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 || color->b < 0 || color->b > 255)
        return (0);
    return (1);
}

int parse_vector(char *str, t_vector *vec)
{
    char **parts = ft_split(str, ',');
    if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
    {
        ft_free_split(parts);
        return (0);
    }
    vec->x = ft_atof(parts[0]);
    vec->y = ft_atof(parts[1]);
    vec->z = ft_atof(parts[2]);
    ft_free_split(parts);
    return (1);
}



static int parse_camera(char *line, t_scene *scene)
{
    char **parts = ft_split(line, ' ');
    if (!parts || !parts[1] || !parts[2] || !parts[3] || parts[4])
    {
        ft_free_split(parts);
        return (0);
    }
    if (!parse_vector(parts[1], &scene->camera.position) ||
        !parse_vector(parts[2], &scene->camera.orientation))
    {
        ft_free_split(parts);
        return (0);
    }
    scene->camera.fov = ft_atoi(parts[3]);
    if (scene->camera.fov < 0 || scene->camera.fov > 180)
    {
        ft_free_split(parts);
        return (0);
    }
    ft_free_split(parts);
    return (1);
}




int parse_scene(char *filename, t_scene *scene)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);

    char *line;
    while ((line = get_next_line(fd)))
    {
        if (ft_strncmp(line, "A ", 2) == 0 && !parse_ambient(line, scene))
            return (0);
        else if (ft_strncmp(line, "C ", 2) == 0 && !parse_camera(line, scene))
            return (0);
        else if (ft_strncmp(line, "L ", 2) == 0 && !parse_light(line, scene))
            return (0);
        else if (ft_strncmp(line, "sp ", 3) == 0 && !parse_sphere(line, scene))
            return (0);
        else if (ft_strncmp(line, "pl ", 3) == 0 && !parse_plane(line, scene))
            return (0);
        else if (ft_strncmp(line, "cy ", 3) == 0 && !parse_cylinder(line, scene))
            return (0);
         else if (ft_strncmp(line, "co ", 3) == 0 && !parse_cone(line, scene))
            return (0);
        free(line);
    }
    close(fd);
    return (1);
}