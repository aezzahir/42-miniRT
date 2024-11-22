#include "../../include/miniRT.h"

t_color	trace_ray(t_ray *ray, t_scene *scene, int depth)
{
	t_intersection	*intersection;
	t_vector		normal;
	t_vector		light_dir;
	t_vector		view_dir;
	t_color			ambient;
	t_color			diffuse;
	t_color			specular;
	float			shadow_factor;
	t_color			local_color;

	if (depth <= 0)
		return (scene->ambient.color);
	intersection = ft_get_nearest_intersection(ray, scene);
	if (!intersection)
		return (color_scale(scene->ambient.color, scene->ambient.ratio));
	normal = ft_get_surface_normal_vector(intersection);
	light_dir = vector_normalize(vector_subtract(scene->light.position,
				intersection->point));
	view_dir = vector_normalize(vector_negate(ray->direction));
	// Basic lighting components
	ambient = calculate_ambient(scene, intersection->color);
	diffuse = calculate_diffuse(scene, normal, light_dir, intersection->color);
	specular = calculate_specular(scene, normal, light_dir, view_dir);
	// Shadow calculation
	ft_enable_intersecton(intersection, 0);
	shadow_factor = calculate_shadow(scene, intersection->point, light_dir);
	ft_enable_intersecton(intersection, 1);
	// Combine basic lighting
	local_color = color_add(ambient, color_scale(color_add(diffuse, specular),
				shadow_factor));
	free(intersection);
	return (local_color);
}

t_ray	ft_generate_ray(float x, float y, t_scene *scene)
{
	float		pixel_x;
	float		pixel_y;
	t_vector	direction;
	t_vector	origin;

	pixel_x = (2.0 * x / WIDTH - 1) * scene->camera.viewport_width / 2;
	pixel_y = (1 - 2.0 * y / HEIGHT) * scene->camera.viewport_height / 2;
	direction = vector_normalize(vector_add(vector_add(vector_multiply(scene->camera.right,
						pixel_x), vector_multiply(scene->camera.up, pixel_y)),
				scene->camera.forward));
	origin = vector_add(scene->camera.position,
			vector_multiply(scene->camera.forward, 0.0001));
	return ((t_ray){origin, direction});
}
