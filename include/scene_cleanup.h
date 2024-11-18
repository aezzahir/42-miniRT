#ifndef SCENE_CLEANUP_H
#define SCENE_CLEANUP_H

void clear_scene(t_scene *scene);
void free_sphere(void *content);
void free_plane(void *content);
void free_cylinder(void *content);
void free_cone(void *content);
bool init_scene(t_scene *scene);
#endif