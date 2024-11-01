#include "../../include/miniRT.h"


t_color apply_checkerboard(t_point point, t_checkerboard cb) {
    int x = (int)(point.x * cb.scale);
    int y = (int)(point.y * cb.scale);
    int z = (int)(point.z * cb.scale);

    if ((x + y + z) % 2 == 0) {
        return cb.color1;
    } else {
        return cb.color2;
    }
}

t_color get_object_color(t_intersection *inter) {
    t_color base_color;
    t_checkerboard cb;

    switch (inter->object_type) {
        case SPH: {
            t_sphere *sphere = (t_sphere *)inter->object;
            base_color = sphere->color;
            cb = sphere->checkerboard;
            break;
        }
        case PLN: {
            t_plane *plane = (t_plane *)inter->object;
            base_color = plane->color;
            cb = plane->checkerboard;
            break;
        }
        case CYL: {
            t_cylinder *cylinder = (t_cylinder *)inter->object;
            base_color = cylinder->color;
            cb = cylinder->checkerboard;
            break;
        }
        case CONE: {
            t_cone *cone = (t_cone *)inter->object;
            base_color = cone->color;
            cb = cone->checkerboard;
            break;
        }
        default:
            return (t_color){0, 0, 0};  // Black for unknown objects
    }

    if (cb.use_checkerboard) {
        return apply_checkerboard(inter->point, cb);
    } else {
        return base_color;
    }
}

void enable_sphere_checkerboard(t_sphere *sphere, float scale, t_color color1, t_color color2) {
    if (sphere) {
        sphere->checkerboard.use_checkerboard = 1;
        sphere->checkerboard.scale = scale;
        sphere->checkerboard.color1 = color1;
        sphere->checkerboard.color2 = color2;
    }
}

void enable_plane_checkerboard(t_plane *plane, float scale, t_color color1, t_color color2) {
    if (plane) {
        plane->checkerboard.use_checkerboard = 1;
        plane->checkerboard.scale = scale;
        plane->checkerboard.color1 = color1;
        plane->checkerboard.color2 = color2;
    }
}

void enable_cylinder_checkerboard(t_cylinder *cylinder, float scale, t_color color1, t_color color2) {
    if (cylinder) {
        cylinder->checkerboard.use_checkerboard = 1;
        cylinder->checkerboard.scale = scale;
        cylinder->checkerboard.color1 = color1;
        cylinder->checkerboard.color2 = color2;
    }
}

void enable_cone_checkerboard(t_cone *cone, float scale, t_color color1, t_color color2) {
    if (cone) {
        cone->checkerboard.use_checkerboard = 1;
        cone->checkerboard.scale = scale;
        cone->checkerboard.color1 = color1;
        cone->checkerboard.color2 = color2;
    }
}

void enable_checkerboard(t_object *object, float scale, t_color color)
{
    switch (object->type) {
        case SPH:
            enable_sphere_checkerboard((t_sphere *)(object->shape), scale, ((t_sphere *)(object->shape))->color, color);
            break;
        case PLN:
            enable_plane_checkerboard((t_plane *)(object->shape), scale, ((t_sphere *)(object->shape))->color, color);
            break;
        case CYL:
            enable_cylinder_checkerboard((t_cylinder *)(object->shape), scale, ((t_sphere *)(object->shape))->color, color);
            break;
        case CONE:
            enable_cone_checkerboard((t_cone *)(object->shape), scale, ((t_sphere *)(object->shape))->color, color);
            break;
        default:
            break;
    }
}