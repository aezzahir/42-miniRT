/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:10:44 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 09:10:45 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int parse_ambient(char *line, t_scene *scene)
{
    char **parts = ft_split(line, ' ');
    if (!parts || !parts[1] || !parts[2] || parts[3])
    {
        ft_free_split(parts);
        return (0);
    }
    scene->ambient.ratio = ft_atof(parts[1]);
    if (scene->ambient.ratio < 0 || scene->ambient.ratio > 1 || !parse_color(parts[2], &scene->ambient.color))
    {
        ft_free_split(parts);
        return (0);
    }
    ft_free_split(parts);
    return (1);
}

int parse_light(char *line, t_scene *scene)
{
    char **parts = ft_split(line, ' ');
    if (!parts || !parts[1] || !parts[2] || !parts[3] || parts[4])
    {
        ft_free_split(parts);
        return (0);
    }
    if (!parse_vector(parts[1], &scene->light.position))
    {
        ft_free_split(parts);
        return (0);
    }
    scene->light.brightness = ft_atof(parts[2]);
    if (scene->light.brightness < 0 || scene->light.brightness > 1 || !parse_color(parts[3], &scene->light.color))
    {
        ft_free_split(parts);
        return (0);
    }
    ft_free_split(parts);
    return (1);
}