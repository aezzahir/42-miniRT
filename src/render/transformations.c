/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:14 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/20 22:13:15 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// Utility functions for rotation
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

// Camera transformation functions
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

void camera_translate(t_camera *camera, t_vector translation) {
    camera->position = vector_add(camera->position, translation);
}

// Object transformation functions
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

void object_translate(t_object *object, t_vector translation)
{
    if (object->type == SPH)
    ((t_sphere *)(object->shape))->center = vector_add(((t_sphere *)(object->shape))->center, translation);
    else if (object->type == PLN)
    ((t_plane *)(object->shape))->point = vector_add(((t_plane *)(object->shape))->point, translation);
    else if (object->type == CYL)
    ((t_cylinder *)(object->shape))->center = vector_add(((t_cylinder *)(object->shape))->center, translation);
    else if (object->type == CONE)
    ((t_cone *)(object->shape))->center = vector_add(((t_cone *)(object->shape))->center, translation);
    else if (object->type == LIGHT)
    ((t_light*)(object->shape))->position = vector_add(((t_light*)(object->shape))->position, translation);
}

static void ft_add_resize(float *d_h, float dx)
{
    if (*d_h + dx >= 0)
        *d_h += dx;
}

void ft_resize_unique_property(t_scene *scene, float d_r, float d_h) {
    t_object *object;

    object = &(scene->selected_object);
    if (object->type == SPH)
    ft_add_resize(&(((t_sphere *)(object->shape))->diameter), d_r);
    else if (object->type == CYL)
    {
    ft_add_resize(&(((t_cylinder *)(object->shape))->diameter), d_r);
    ft_add_resize(&(((t_cylinder *)(object->shape))->height), d_h);
    }
    else if (object->type == CONE)
    {
    ft_add_resize(&(((t_cone *)(object->shape))->diameter), d_r);
    ft_add_resize(&(((t_cone *)(object->shape))->height), d_h);
    }
}
void change_color(t_object *object, t_color color) {
    if (object->type == SPH)
        color_add_ptr(&(((t_sphere *)(object->shape))->color), color);
    else if (object->type == PLN)
        color_add_ptr(&(((t_plane *)(object->shape))->color), color);
    else if (object->type == CYL)
        color_add_ptr(&(((t_cylinder *)(object->shape))->color), color);
    else if (object->type == CONE)
         color_add_ptr(&(((t_cone *)(object->shape))->color), color);
    else if (object->type == LIGHT)
        color_add_ptr(&(((t_light *)(object->shape))->color), color);
}
// Scene transformation function
void transform_scene(t_scene *scene, t_vector rotation, t_vector translation, t_color color) {
    // Transform camera
    if (scene->selected_object.type == CAM)
    {
        camera_rotate(&scene->camera, rotation);
        camera_translate(&scene->camera, translation);
        ft_setup_camera(&scene->camera); // recalculate the camera parameters
    }
    else
    {
        object_rotate(&(scene->selected_object), rotation);
        object_translate(&(scene->selected_object), translation);
        change_color(&(scene->selected_object), color);
    }
}

