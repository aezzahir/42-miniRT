#ifndef GEOMETRY_H
#define GEOMETRY_H\

typedef struct s_scene t_scene;
#include "miniRT.h"
// Sphere structure

typedef enum s_object_type {
    CYL,
    PLN,
    SPH,
    CONE,
    CAM,
    LIGHT
} t_object_type;

typedef struct s_material {
    float reflectivity;     // 0.0 to 1.0
    float transparency;     // 0.0 to 1.0
    float refraction_index; // Typically 1.0 (air) to 2.4 (diamond)
    float specularity;      // Controls the size of specular highlights          // Base color of the object
} t_material;

typedef struct s_sphere {
    t_vector center;
    float diameter;
    t_color color;
    t_material *material;
    int enable_intersection;
} t_sphere;

//
// Intersection structure
typedef struct s_intersection {
    float t;
    t_color color;
    t_vector normal;
    t_vector point;
    void *object;
    t_object_type object_type;
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
    t_material *material;
    int enable_intersection;
} t_cylinder;


t_cylinder *create_cylinder(t_point center, t_vector axis, float diameter, float height, t_color color);
t_intersection *intersect_cylinder(t_ray *ray, t_cylinder *cylinder);
t_intersection *intersect_lst_cylinders(t_ray *ray, t_scene *scene);
t_vector calculate_cylinder_normal(t_cylinder *cylinder, t_point intersection_point);
void ft_print_cylinder(void *content);


//// --------------------- planes 


typedef struct s_plane {
    t_point point;
    t_vector normal;
    t_color color;
    t_material *material;
    int enable_intersection;
} t_plane;

t_plane *create_plane(t_point point, t_vector normal, t_color color);
t_intersection *intersect_plane(t_ray *ray, t_plane *plane);
t_intersection *intersect_lst_planes(t_ray *ray, t_scene *scene);
t_intersection *ft_get_nearest_intersection(t_ray *ray, t_scene *scene);


typedef struct s_cone
{
    t_vector center;  // Base center of the cone
    t_vector axis;    // Direction vector of the cone's axis
    float diameter;  // Base diameter of the cone
    float height;    // Height of the cone
    t_color color;    // Color of the cone
    int enable_intersection;
} t_cone;

void ft_print_cone(void *content);
t_cone *create_cone(t_point center, t_vector axis, float diameter, float height, t_color color);
t_intersection *intersect_cone(t_ray *ray, t_cone *cone);
t_intersection *intersect_lst_cones(t_ray *ray, t_scene *scene);
t_vector calculate_cone_normal(t_cone *cone, t_point hit_point);
#endif