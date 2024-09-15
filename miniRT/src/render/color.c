#include "../../include/miniRT.h"

t_color color_scale(t_color color, float scalar)
{
    return (t_color){
        fminf(color.r * scalar, 255),
        fminf(color.g * scalar, 255),
        fminf(color.b * scalar, 255)
    };
}

t_color color_add(t_color c1, t_color c2) {
    return (t_color){
        fminf(c1.r + c2.r, 255),
        fminf(c1.g + c2.g, 255),
        fminf(c1.b + c2.b, 255)
    };
}

t_color color_multiply(t_color c1, t_color c2) {
    return (t_color){
        (c1.r * c2.r) / 255,
        (c1.g * c2.g) / 255,
        (c1.b * c2.b) / 255
    };
}

int color_to_int(t_color color)
{
    return ((int)color.r << 16) | ((int)color.g << 8) | (int)color.b;
}

t_color int_to_color(int color_int) {
    return (t_color){
        (color_int >> 16) & 0xFF,
        (color_int >> 8) & 0xFF,
        color_int & 0xFF
    };
}

t_color add_shade(double distance,  t_color color) {
    float shade_factor = 1.0 - fminf(fmaxf(distance, 0.0), 1.0);
    t_color shaded_color = color_scale(color, shade_factor);
    return shaded_color;
}

int get_opposite(int color) {
    t_color color_struct = int_to_color(color);
    t_color opposite = {
        255 - color_struct.r,
        255 - color_struct.g,
        255 - color_struct.b
    };
    return color_to_int(opposite);
}