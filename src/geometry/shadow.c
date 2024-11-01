bool check_shadow(t_vector point, t_vector light_dir, t_scene *scene)
{
    t_ray shadow_ray;
    float light_distance;
    t_intersection *shadow_hit;

    shadow_ray.origin = vector_add(point, vector_multiply(light_dir, 0.001)); // Offset to avoid self-intersection
    shadow_ray.direction = light_dir;
    
    light_distance = vector_length(vector_subtract(scene->light.position, point));

    // Check intersection with all objects in the scene
    shadow_hit = intersect_sphere(&shadow_ray, &(scene->sphere));
    
    if (shadow_hit && shadow_hit->t < light_distance)
    {
        free(shadow_hit);
        return true; // Shadow ray hit an object before reaching the light
    }
    
    free(shadow_hit);
    return false; // No shadow
}