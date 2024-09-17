#include "../../include/miniRT.h"

// Utility functions for rotation
t_vector rotate_x(t_vector v, float angle) {
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);
    return (t_vector){
        v.x,
        v.y * cos_a - v.z * sin_a,
        v.y * sin_a + v.z * cos_a
    };
}

t_vector rotate_y(t_vector v, float angle) {
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);
    return (t_vector){
        v.x * cos_a + v.z * sin_a,
        v.y,
        -v.x * sin_a + v.z * cos_a
    };
}

t_vector rotate_z(t_vector v, float angle) {
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);
    return (t_vector){
        v.x * cos_a - v.y * sin_a,
        v.x * sin_a + v.y * cos_a,
        v.z
    };
}

// Camera transformation functions
void camera_rotate(t_camera *camera, t_vector rotation) {
    camera->orientation = rotate_x(camera->orientation, rotation.x);
    camera->orientation = rotate_y(camera->orientation, rotation.y);
    camera->orientation = rotate_z(camera->orientation, rotation.z);
    
    camera->up = rotate_x(camera->up, rotation.x);
    camera->up = rotate_y(camera->up, rotation.y);
    camera->up = rotate_z(camera->up, rotation.z);
    
    camera->right = vector_cross_product(camera->orientation, camera->up);
    camera->up = vector_cross_product(camera->right, camera->orientation);
}

void camera_translate(t_camera *camera, t_vector translation) {
    camera->position = vector_add(camera->position, translation);
}

// Object transformation functions
void object_rotate(t_object *object, t_vector rotation) {
    switch (object->type) {
        case PLN:
            ((t_plane *)(object->shape))->normal = rotate_x(((t_plane *)(object->shape))->normal, rotation.x);
            ((t_plane *)(object->shape))->normal = rotate_y(((t_plane *)(object->shape))->normal, rotation.y);
            ((t_plane *)(object->shape))->normal = rotate_z(((t_plane *)(object->shape))->normal, rotation.z);
            break;
        case CYL:
            ((t_cylinder *)(object->shape))->axis = rotate_x(((t_cylinder *)(object->shape))->axis, rotation.x);
            ((t_cylinder *)(object->shape))->axis = rotate_y(((t_cylinder *)(object->shape))->axis, rotation.y);
            ((t_cylinder *)(object->shape))->axis = rotate_z(((t_cylinder *)(object->shape))->axis, rotation.z);
            break;
        case CONE:
            ((t_cone *)(object->shape))->axis = rotate_x(((t_cone *)(object->shape))->axis, rotation.x);
            ((t_cone *)(object->shape))->axis = rotate_y(((t_cone *)(object->shape))->axis, rotation.y);
            ((t_cone *)(object->shape))->axis = rotate_z(((t_cone *)(object->shape))->axis, rotation.z);
            break;
        default:
            break;

    }
}

void object_translate(t_object *object, t_vector translation) {
    switch (object->type) {
        case SPH:
            ((t_sphere *)(object->shape))->center = vector_add(((t_sphere *)(object->shape))->center, translation);
            break;
        case PLN:
           ((t_plane *)(object->shape))->point = vector_add(((t_plane *)(object->shape))->point, translation);
            break;
        case CYL:
            ((t_cylinder *)(object->shape))->center = vector_add(((t_cylinder *)(object->shape))->center, translation);
            break;
        case CONE:
            ((t_cone *)(object->shape))->center = vector_add(((t_cone *)(object->shape))->center, translation);
            break;
        case LIGHT:
            ((t_light*)(object->shape))->position = vector_add(((t_light*)(object->shape))->position, translation);
            break;
        default:
            break;
    }
}

static void ft_add_resize(float *d_h, float dx)
{
    if (*d_h + dx >= 0)
        *d_h += dx;
}

void ft_resize_unique_property(t_scene *scene, float d_r, float d_h) {
    t_object *object;

    object = &(scene->selected_object);
    switch (object->type) {
        case SPH:
            ft_add_resize(&(((t_sphere *)(object->shape))->diameter), d_r);
            break;
        case CYL:
            ft_add_resize(&(((t_cylinder *)(object->shape))->diameter), d_r);
            ft_add_resize(&(((t_cylinder *)(object->shape))->height), d_h);
            break;
        case CONE:
            ft_add_resize(&(((t_cone *)(object->shape))->diameter), d_r);
            ft_add_resize(&(((t_cone *)(object->shape))->height), d_h);
            break;
        default:
            break;

    }
}

// Scene transformation function
void transform_scene(t_scene *scene, t_vector rotation, t_vector translation) {
    // Transform camera
    if (scene->selected_object.type == CAM)
    {
        camera_rotate(&scene->camera, rotation);
        camera_translate(&scene->camera, translation);
    }
    else
    {
        object_rotate(&(scene->selected_object), rotation);
        object_translate(&(scene->selected_object), translation);
    }
}

