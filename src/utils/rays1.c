#include "../../include/miniRT.h"

t_color	handle_no_intersection(t_scene *scene)
{
	return (color_scale(scene->ambient.color, scene->ambient.ratio));
}

t_lighting_vectors	calculate_vectors(t_scene *scene,
		t_intersection *intersection, t_ray *ray)
{
	t_lighting_vectors	vectors;

	vectors.normal = ft_get_surface_normal_vector(intersection);
	vectors.light_dir = vector_normalize(vector_subtract(scene->light.position,
				intersection->point));
	vectors.view_dir = vector_normalize(vector_negate(ray->direction));
	return (vectors);
}
