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