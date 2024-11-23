/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:04:23 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 11:33:26 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define SHADOW_SAMPLES 16
# define WATER_REFRACTIVE_INDEX 1.33
# define WATER_TRANSPARENCY 0.8
# define WATER_REFLECTIVITY 0.2

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_color_sums
{
    float r_sum;
    float g_sum;
    float b_sum;
} t_color_sums;

typedef struct s_pixel_coords
{
    int x;
    int y;
    int dx;
    int dy;
} t_pixel_coords;

t_color	color_scale(t_color color, float scalar);
t_color	color_add(t_color c1, t_color c2);
t_color	color_multiply(t_color c1, t_color c2);
int		color_to_int(t_color color);
void	color_add_ptr(t_color *c1, t_color c2);

#endif