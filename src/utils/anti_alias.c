/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:12 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 17:04:18 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

#define AA_SAMPLES 2 // 4x4 supersampling

// Function to calculate the color for a single subpixel
static t_color get_subpixel_color(t_scene *scene, int x, int y, int dx, int dy)
{
    float subpixel_x = x + (dx + 0.5f) / AA_SAMPLES;
    float subpixel_y = y + (dy + 0.5f) / AA_SAMPLES;
    t_ray ray = ft_generate_ray(subpixel_x, subpixel_y, scene);
    return trace_ray(&ray, scene, MAX_DEPTH);
}

// Function to accumulate color values from all subpixels
static void accumulate_colors(int dx, int dy, t_scene *scene, int x, int y, float *r_sum, float *g_sum, float *b_sum)
{
    t_color subpixel_color = get_subpixel_color(scene, x, y, dx, dy);
    *r_sum += subpixel_color.r;
    *g_sum += subpixel_color.g;
    *b_sum += subpixel_color.b;
}

// Main anti-aliasing function
t_color anti_alias_pixel(t_scene *scene, int x, int y)
{
    (void)x;
    (void)y;

    float r_sum = 0;
    float g_sum = 0;
    float b_sum = 0;
    int dx = 0;
    int dy;

    while (dx < AA_SAMPLES)
    {
        dy = 0;
        while (dy < AA_SAMPLES)
        {
            accumulate_colors(dx, dy, scene, x, y, &r_sum, &g_sum, &b_sum);
            dy++;
        }
        dx++;
    }

    int total_samples = AA_SAMPLES * AA_SAMPLES;
    t_color color_sum = {r_sum / total_samples, g_sum / total_samples, b_sum / total_samples};
    
    return color_sum;
}

