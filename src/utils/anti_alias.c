/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:12 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 09:13:10 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

#define AA_SAMPLES 2

static t_color	get_subpixel_color(t_scene *scene, int x, int y, int dx, int dy)
{
	float	subpixel_x;
	float	subpixel_y;
	t_ray	ray;

	subpixel_x = x + (dx + 0.5f) / AA_SAMPLES;
	subpixel_y = y + (dy + 0.5f) / AA_SAMPLES;
	ray = ft_generate_ray(subpixel_x, subpixel_y, scene);
	return (trace_ray(&ray, scene, MAX_DEPTH));
}

static void	accumulate_colors(int dx, int dy, t_scene *scene, int x, int y,
		float *r_sum, float *g_sum, float *b_sum)
{
	t_color	subpixel_color;

	subpixel_color = get_subpixel_color(scene, x, y, dx, dy);
	*r_sum += subpixel_color.r;
	*g_sum += subpixel_color.g;
	*b_sum += subpixel_color.b;
}

t_color	anti_alias_pixel(t_scene *scene, int x, int y)
{
	float	r_sum;
	float	g_sum;
	float	b_sum;
	int		dx;
	int		dy;
	int		total_samples;
	t_color	color_sum;

	(void)x;
	(void)y;
	r_sum = 0;
	g_sum = 0;
	b_sum = 0;
	dx = 0;
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
	total_samples = AA_SAMPLES * AA_SAMPLES;
	color_sum = {r_sum / total_samples, g_sum / total_samples, b_sum
		/ total_samples};
	return (color_sum);
}
