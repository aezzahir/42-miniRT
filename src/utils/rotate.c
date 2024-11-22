#include "../../include/miniRT.h"

t_vector rotate_x(t_vector v, float angle)
{

    float cos_a;
    float sin_a;

    cos_a = cosf(angle);
    sin_a = sinf(angle);
    return (t_vector){
        v.x,
        v.y * cos_a - v.z * sin_a,
        v.y * sin_a + v.z * cos_a
    };
}

t_vector rotate_y(t_vector v, float angle)
{
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);
    return (t_vector){
        v.x * cos_a + v.z * sin_a,
        v.y,
        -v.x * sin_a + v.z * cos_a
    };
}

t_vector rotate_z(t_vector v, float angle)
{
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);
    return (t_vector){
        v.x * cos_a - v.y * sin_a,
        v.x * sin_a + v.y * cos_a,
        v.z
    };
}

void object_rotate(t_object *o, t_vector r)
{
        
        if (o->type == PLN) 
        {
            ((t_plane *)(o->shape))->normal = rotate_x(((t_plane *)(o->shape))->normal, r.x);
            ((t_plane *)(o->shape))->normal = rotate_y(((t_plane *)(o->shape))->normal, r.y);
            ((t_plane *)(o->shape))->normal = rotate_z(((t_plane *)(o->shape))->normal, r.z);
        }
        else if (o->type == CYL)
        {
            ((t_cylinder *)(o->shape))->axis = rotate_x(((t_cylinder *)(o->shape))->axis, r.x);
            ((t_cylinder *)(o->shape))->axis = rotate_y(((t_cylinder *)(o->shape))->axis, r.y);
            ((t_cylinder *)(o->shape))->axis = rotate_z(((t_cylinder *)(o->shape))->axis, r.z);
        }
        else if (o->type == CONE)
        {
            ((t_cone *)(o->shape))->axis = rotate_x(((t_cone *)(o->shape))->axis, r.x);
            ((t_cone *)(o->shape))->axis = rotate_y(((t_cone *)(o->shape))->axis, r.y);
            ((t_cone *)(o->shape))->axis = rotate_z(((t_cone *)(o->shape))->axis, r.z);
        }

}

void camera_rotate(t_camera *camera, t_vector rotation)
{
    camera->orientation = rotate_x(camera->orientation, rotation.x);
    camera->orientation = rotate_y(camera->orientation, rotation.y);
    camera->orientation = rotate_z(camera->orientation, rotation.z);
    
    camera->up = rotate_x(camera->up, rotation.x);
    camera->up = rotate_y(camera->up, rotation.y);
    camera->up = rotate_z(camera->up, rotation.z);
    
    camera->right = vector_cross_product(camera->orientation, camera->up);
    camera->up = vector_cross_product(camera->right, camera->orientation);
}