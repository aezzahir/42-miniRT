#include "../../include/miniRT.h"

#define AA_SAMPLES 2  // 4x4 supersampling

t_color anti_alias_pixel(t_scene *scene, int x, int y) 
{
    (void)x;
    (void)y;
    t_color color_sum = {0, 0, 0};
    float r_sum = 0, g_sum = 0, b_sum = 0;

    for (int dx = 0; dx < AA_SAMPLES; dx++) {
        for (int dy = 0; dy < AA_SAMPLES; dy++) {
            float subpixel_x = x + (dx + 0.5f) / AA_SAMPLES;
            float subpixel_y = y + (dy + 0.5f) / AA_SAMPLES;

            t_ray ray = ft_generate_ray(subpixel_x, subpixel_y, scene);
            t_color subpixel_color = trace_ray(&ray, scene, MAX_DEPTH);

            r_sum += subpixel_color.r;
            g_sum += subpixel_color.g;
            b_sum += subpixel_color.b;
        }
    }

    int total_samples = AA_SAMPLES * AA_SAMPLES;
    color_sum.r = r_sum / total_samples;
    color_sum.g = g_sum / total_samples;
    color_sum.b = b_sum / total_samples;

    return color_sum;
}