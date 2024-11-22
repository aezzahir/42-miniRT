/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:13:14 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 08:50:36 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void camera_translate(t_camera *camera, t_vector translation) {
    camera->position = vector_add(camera->position, translation);
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

