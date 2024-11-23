/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:12 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 11:35:37 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

#define AA_SAMPLES 2

static t_color get_subpixel_color(t_scene *scene, t_pixel_coords coords)
{
    float subpixel_x;
    float subpixel_y;
    t_ray ray;
    
    subpixel_x = coords.x + (coords.dx + 0.5f) / AA_SAMPLES;
    subpixel_y = coords.y + (coords.dy + 0.5f) / AA_SAMPLES;
    ray = ft_generate_ray(subpixel_x, subpixel_y, scene);
    return (trace_ray(&ray, scene, MAX_DEPTH));
}

static void accumulate_colors(t_scene *scene, t_pixel_coords coords, 
    t_color_sums *sums)
{
    t_color subpixel_color;
    
    subpixel_color = get_subpixel_color(scene, coords);
    sums->r_sum += subpixel_color.r;
    sums->g_sum += subpixel_color.g;
    sums->b_sum += subpixel_color.b;
}

static t_color_sums calculate_color_sums(t_scene *scene, int x, int y)
{
    t_color_sums sums;
    t_pixel_coords coords;
    int dx;
    int dy;
    
    sums.r_sum = 0;
    sums.g_sum = 0;
    sums.b_sum = 0;
    coords.x = x;
    coords.y = y;
    dx = 0;
    while (dx < AA_SAMPLES)
    {
        dy = 0;
        while (dy < AA_SAMPLES)
        {
            coords.dx = dx;
            coords.dy = dy;
            accumulate_colors(scene, coords, &sums);
            dy++;
        }
        dx++;
    }
    return (sums);
}

t_color anti_alias_pixel(t_scene *scene, int x, int y)
{
    t_color_sums sums;
    t_color color_sum;
    int total_samples;
    
    (void)x;
    (void)y;
    sums = calculate_color_sums(scene, x, y);
    total_samples = AA_SAMPLES * AA_SAMPLES;
    
    color_sum.r = sums.r_sum / total_samples;
    color_sum.g = sums.g_sum / total_samples;
    color_sum.b = sums.b_sum / total_samples;
    
    return (color_sum);
}
