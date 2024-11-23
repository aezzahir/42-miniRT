#ifndef GEOMETRY_H
#define GEOMETRY_H\

typedef struct s_scene t_scene;
#include "miniRT.h"
// Sphere structure
typedef enum s_object_type
{
	CYL,
	PLN,
	SPH,
	CONE,
	CAM,
	LIGHT,
	NONE
}						t_object_type;

typedef struct s_material
{
	float				reflectivity;
	float				transparency;
	float				refraction_index;
	float				specularity;

}						t_material;

typedef struct s_sphere
{
	t_vector			center;
	float				diameter;
	t_color				color;
	t_material			*material;
	int					enable_intersection;
}						t_sphere;

//
// Intersection structure
typedef struct s_intersection
{
	float				t;
	t_color				color;
	t_vector			normal;
	t_vector			point;
	void				*object;
	t_object_type		object_type;
}						t_intersection;

// t_ray structeur R(t) = Origin + t . Direction
typedef struct s_ray
{
	t_point				origin;
	t_vector			direction;
}						t_ray;

t_sphere				*create_sphere(t_point origin, float diameter,
							t_color color);
void					ft_print_sphere(void *content);

// -------------------------- Intersection With Sphere ---------------------------------------

typedef struct s_cylinder
{
	t_point				center;
	t_vector			axis;
	float				diameter;
	float				height;
	t_color				color;
	t_material			*material;
	int					enable_intersection;
}						t_cylinder;

t_vector calculate_cylinder_normal(t_cylinder *cylinder, t_point intersection_point);
float	get_bottom_cap_distance(t_ray *ray, t_cylinder *cyl, float denom);

//// --------------------- planes 


typedef struct s_plane {
    t_point point;
    t_vector normal;
    t_color color;
    t_material *material;
    int enable_intersection;
} t_plane;

t_plane					*create_plane(t_point point, t_vector normal,
							t_color color);
t_intersection			*ft_get_nearest_intersection(t_ray *ray,
							t_scene *scene);

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
t_vector calculate_cone_normal(t_cone *cone, t_point hit_point);
t_vector	get_perpendicular_vector(t_vector v, t_vector x);
float	calculate_discriminant(t_vector v, t_vector oc_perp, float radius);
float	solve_quadratic(float a, float b, float discriminant);
bool	is_within_body(t_point body_hit, t_cylinder *cyl);
float	get_bottom_cap_distance(t_ray *ray, t_cylinder *cyl, float denom);

float					get_sphere_distance(t_ray *ray, t_sphere *sphere);
float					get_plane_distance(t_ray *ray, t_plane *plane);
float					get_cylinder_distance(t_ray *ray, t_cylinder *cyl);
float					get_cone_distance(t_ray *ray, t_cone *cone);

t_vector	rotate_x(t_vector v, float angle);
t_vector	rotate_y(t_vector v, float angle);
t_vector	rotate_z(t_vector v, float angle);

#endif