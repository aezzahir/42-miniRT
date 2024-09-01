#ifndef COLOR_H
#define COLOR_H

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

t_color color_scale(t_color color, float scalar);
t_color color_add(t_color c1, t_color c2);
t_color color_multiply(t_color c1, t_color c2);
#endif