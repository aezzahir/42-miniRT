/*
 * cylinder.c
 * Implements cylinder intersection and normal calculations
 */
#include "../../include/miniRT.h"

t_cylinder *create_cylinder(t_point center, t_vector axis, float diameter, float height, t_color color)
{
    t_cylinder *cylinder = NULL;

    cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
    if (!cylinder)
    {
        printf("malloc error in create_cylinder\n");
        return (NULL);
    }

    cylinder->center = center;
    cylinder->axis = vector_normalize(axis);  // Ensure the axis is normalized
    cylinder->diameter = diameter;
    cylinder->height = height;
    cylinder->color = color;

    return (cylinder);
}

t_intersection *intersect_cylinder(t_ray *ray, t_cylinder *cyl) {
    t_vector oc = vector_subtract(ray->origin, cyl->center); // Ray origin to cylinder center
    float radius = cyl->diameter / 2;

    if (cyl->enable_intersection != 1)
        return (NULL);
    // Step 1: Cylinder body intersection
    t_vector v_dir_perpendicular = vector_subtract(ray->direction, 
                    vector_multiply(cyl->axis, vector_dot_product(ray->direction, cyl->axis)));
    t_vector oc_perpendicular = vector_subtract(oc, 
                    vector_multiply(cyl->axis, vector_dot_product(oc, cyl->axis)));
    
    float a = vector_dot_product(v_dir_perpendicular, v_dir_perpendicular);
    float b = 2 * vector_dot_product(v_dir_perpendicular, oc_perpendicular);
    float c = vector_dot_product(oc_perpendicular, oc_perpendicular) - radius * radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return NULL;  // No intersection with cylinder body
    
    // Solving quadratic equation for t
    float sqrt_discriminant = sqrt(discriminant);
    float t1 = (-b - sqrt_discriminant) / (2 * a);
    float t2 = (-b + sqrt_discriminant) / (2 * a);

    // Step 2: Check if body intersection is within the height of the finite cylinder
    float t_body = (t1 >= 0) ? t1 : t2;
    if (t_body < 0) return NULL; // Both solutions are behind the ray
    
    t_point body_hit_point = vector_add(ray->origin, vector_multiply(ray->direction, t_body));
    float body_height = vector_dot_product(vector_subtract(body_hit_point, cyl->center), cyl->axis);
    bool is_body_hit_valid = (body_height >= 0 && body_height <= cyl->height);

    // Step 3: Cap intersections
    float t_bottom = vector_dot_product(vector_subtract(cyl->center, ray->origin), cyl->axis) /
                     vector_dot_product(ray->direction, cyl->axis);
    float t_top = vector_dot_product(vector_subtract(vector_add(cyl->center, vector_multiply(cyl->axis, cyl->height)), ray->origin), cyl->axis) /
                  vector_dot_product(ray->direction, cyl->axis);

    t_point bottom_cap_point = vector_add(ray->origin, vector_multiply(ray->direction, t_bottom));
    t_point top_cap_point = vector_add(ray->origin, vector_multiply(ray->direction, t_top));

    bool valid_bottom_cap = (vector_distance(bottom_cap_point, cyl->center) <= radius);
    bool valid_top_cap = (vector_distance(top_cap_point, vector_add(cyl->center, vector_multiply(cyl->axis, cyl->height))) <= radius);

    // Step 4: Choose the nearest valid intersection
    float t = INFINITY;
    int hit_type = 0; // 0: body, 1: bottom cap, 2: top cap

    if (is_body_hit_valid) {
        t = t_body;
        hit_type = 0;
    }

    if (valid_bottom_cap && t_bottom > 0 && t_bottom < t) {
        t = t_bottom;
        hit_type = 1;
    }

    if (valid_top_cap && t_top > 0 && t_top < t) {
        t = t_top;
        hit_type = 2;
    }

    if (t == INFINITY) return NULL; // No intersection

    // Step 5: Create the intersection object
    t_intersection *intersection = malloc(sizeof(t_intersection));
    if (!intersection) return NULL;

    intersection->point = vector_add(ray->origin, vector_multiply(ray->direction, t));
    intersection->t = t;
    intersection->object = cyl;
    intersection->color = cyl->color;
    intersection->object_type = CYL;

    // Calculate normal based on hit type
    if (hit_type == 0) {
        // Hit on cylinder body
        t_vector cp = vector_subtract(intersection->point, cyl->center);
        t_vector projection = vector_multiply(cyl->axis, vector_dot_product(cp, cyl->axis));
        intersection->normal = vector_normalize(vector_subtract(cp, projection));
    } else if (hit_type == 1) {
        // Hit on bottom cap
        intersection->normal = vector_negate(cyl->axis);
    } else {
        // Hit on top cap
        intersection->normal = cyl->axis;
    }

    return intersection;
}


t_intersection *intersect_lst_cylinders(t_ray *ray, t_scene *scene)
{
    t_list *current = NULL;
    t_cylinder *cylinder;
    t_intersection *intersection, *nearest_intersection = NULL;

    if (scene->cylinders && *(scene->cylinders))
        current = *(scene->cylinders);
    else
        return (NULL);

    while (current)
    {
        cylinder = (t_cylinder *)(current->content);
        intersection = intersect_cylinder(ray, cylinder);
        if (intersection && (!nearest_intersection || (nearest_intersection && intersection->t < nearest_intersection->t)))
        {
            if (nearest_intersection)
                free(nearest_intersection);
            nearest_intersection = intersection;
        }
        else if (intersection)
        {
            free(intersection);
        }
        current = current->next;
    }
    return (nearest_intersection);
}

t_vector calculate_cylinder_normal(t_cylinder *cyl, t_point hit_point) {
    // Vector from cylinder base center to hit point
    t_vector cp = vector_subtract(hit_point, cyl->center);
    
    // Project the vector cp onto the cylinder's axis
    float projection_length = vector_dot_product(cp, cyl->axis);
    
    // If the hit is on the bottom cap
    if (projection_length <= 0) {
        return vector_negate(cyl->axis);  // Normal is opposite to the cylinder's axis for the bottom cap
    }
    
    // If the hit is on the top cap
    if (projection_length >= cyl->height) {
        return cyl->axis;  // Normal is the same as the cylinder's axis for the top cap
    }
    
    // Hit on the cylinder body
    // Remove the component of cp along the axis to get the normal on the cylinder body
    t_vector projection = vector_multiply(cyl->axis, projection_length);
    t_vector normal = vector_subtract(cp, projection);  // This gives the vector perpendicular to the axis
    return vector_normalize(normal);  // Normalize the result to get the normal direction
}




void ft_print_cylinder(void *content)
{
    t_cylinder *cylinder;

    cylinder = (t_cylinder *)content;
    printf("Cylinder: center (%2f, %2f, %2f), axis (%2f, %2f, %2f), diameter %2f, height %2f\n",
           cylinder->center.x, cylinder->center.y, cylinder->center.z,
           cylinder->axis.x, cylinder->axis.y, cylinder->axis.z,
           cylinder->diameter, cylinder->height);
}