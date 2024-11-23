/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:07:43 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/23 09:32:35 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

typedef struct s_scene	t_scene;
# include "miniRT.h"

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

t_cylinder				*create_cylinder(t_point center, t_vector axis,
							float diameter, float height, t_color color);
t_vector				calculate_cylinder_normal(t_cylinder *cylinder,
							t_point intersection_point);

//// --------------------- planes
typedef struct s_plane
{
	t_point				point;
	t_vector			normal;
	t_color				color;
	t_material			*material;
	int					enable_intersection;
}						t_plane;

t_plane					*create_plane(t_point point, t_vector normal,
							t_color color);
t_intersection			*ft_get_nearest_intersection(t_ray *ray,
							t_scene *scene);

typedef struct s_cone
{
	t_vector			center;
	t_vector			axis;
	float				diameter;
	float				height;
	t_color				color;
	int					enable_intersection;
}						t_cone;

t_cone					*create_cone(t_point center, t_vector axis,
							float diameter, float height, t_color color);
t_vector				calculate_cone_normal(t_cone *cone, t_point hit_point);

float					get_sphere_distance(t_ray *ray, t_sphere *sphere);
float					get_plane_distance(t_ray *ray, t_plane *plane);
float					get_cylinder_distance(t_ray *ray, t_cylinder *cyl);
float					get_cone_distance(t_ray *ray, t_cone *cone);
#endif