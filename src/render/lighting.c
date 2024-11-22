/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:06 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 05:25:03 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * lighting.c
 * Implements lighting calculations
 * Manages ambient, diffuse, and shadow computations
 */
#include "../../include/miniRT.h"

t_color calculate_ambient(t_scene *scene, t_color object_color) {
    return color_multiply(color_scale(scene->ambient.color, scene->ambient.ratio), object_color);
}

t_color calculate_diffuse(t_scene *scene, t_vector normal, t_vector light_dir, t_color object_color) {
    float diff = fmaxf(vector_dot_product(normal, light_dir), 0.0);
    return color_multiply(color_scale(scene->light.color, diff * scene->light.brightness), object_color);
}

t_color calculate_specular(t_scene *scene, t_vector normal, t_vector light_dir,
                           t_vector view_dir)
{
    float ks;
    float shininess;
    t_vector reflect_dir;
    float cos_alpha;
    float spec;
    float intensity;

    ks = 0.8;
    shininess = 32.0;
    reflect_dir = vector_reflect(vector_negate(light_dir), normal);
    cos_alpha = fmaxf(vector_dot_product(view_dir, reflect_dir), 0.0);
    spec = ks * powf(cos_alpha, shininess);
    intensity = spec * scene->light.brightness;

    return color_scale(scene->light.color, intensity);
}


float calculate_shadow(t_scene *scene, t_point hit_point, t_vector light_dir) {
    float light_distance = vector_length(vector_subtract(scene->light.position, hit_point));
    
    t_ray shadow_ray = {hit_point, light_dir};
    t_intersection *shadow_intersection = ft_get_nearest_intersection(&shadow_ray, scene);
    
    if (shadow_intersection && shadow_intersection->t < 0.99 * light_distance) {
        free(shadow_intersection);
        return 0.0;  // Full shadow
    }
    
    if (shadow_intersection) {
        free(shadow_intersection);
    }
    
    return 1.0;  // No shadow
}




