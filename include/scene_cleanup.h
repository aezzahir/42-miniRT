/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_cleanup.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:08:08 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/20 22:08:09 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_CLEANUP_H
#define SCENE_CLEANUP_H

void clear_scene(t_scene *scene);
void free_sphere(void *content);
void free_plane(void *content);
void free_cylinder(void *content);
void free_cone(void *content);
bool init_scene(t_scene *scene);
#endif