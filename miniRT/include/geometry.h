#ifndef GEOMETRY_H
#define GEOMETRY_H\

typedef struct s_scene t_scene;
#include "miniRT.h"
// Sphere structure

typedef struct s_sphere {
    t_vector center;
    float diameter;
    t_color color;
} t_sphere;

//
// Intersection structure
typedef struct s_intersection {
    float t;
    t_color color;
    t_vector normal;
    t_vector point;
    void *object;
} t_intersection;

// t_ray structeur R(t) = Origin + t . Direction 
typedef struct s_ray {
    t_point origin;  // origin of ray is a point on the 3D space
    t_vector direction; // direction of ray is   a vector on the 3D space
} t_ray;

t_sphere *create_sphere(t_point origin, float diameter, t_color color);
t_intersection *intersect_sphere(t_ray *ray, t_sphere *sphere);
t_intersection *intersect_lst_spheres(t_ray *ray, t_scene *scene);
void ft_print_sphere(void *content);

// -------------------------- Intersection With Sphere ---------------------------------------


typedef struct s_cylinder {
    t_point center;
    t_vector axis;
    float diameter;
    float height;
    t_color color;
} t_cylinder;
t_cylinder *create_cylinder(t_point center, t_vector axis, float diameter, float height, t_color color);
t_intersection *intersect_cylinder(t_ray *ray, t_cylinder *cylinder);
t_intersection *intersect_lst_cylinders(t_ray *ray, t_scene *scene);
void ft_print_cylinder(void *content);

#endif