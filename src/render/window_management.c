#include "../../include/miniRT.h"

void my_pixel_put(t_img *img, int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    int offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
    *((unsigned int *)(img->img_pixel_ptr + offset)) = color;
}



int expose_hook(t_mlx_data *data) {
    data->redraw_needed = 1;  // Set redraw flag
    return 0;
}
int key_hook(int keycode, t_mlx_data *data) {
    // printf("key released --> %d\n", keycode);
    if (keycode == 65307) {  // ESC key
        ft_close(data);
    }
    if (keycode == 'c') {
        data->scene->selected_object.type = CAM;
    }
    if (keycode == 'l') {
        data->scene->selected_object.type = LIGHT;
        data->scene->selected_object.shape = &(data->scene->light);
        // printf("Light's position: ");
        vector_print(data->scene->light.position);
    }
    if (keycode == 'r') {
        data->redraw_needed = 1;
    }
    
    // Handle transformations
    handle_user_input(keycode, data->scene);
    
    // Set redraw flag after any transformation
    data->redraw_needed = 1;
    
    return 0;
}

int key_press(int keycode, t_mlx_data *data) {
    // printf("Key pressed: %d\n", keycode);
    handle_user_input(keycode, data->scene);
    return (0);
}

int handle_user_input(int key, t_scene *scene) {
    t_vector rotation = {0, 0, 0};
    t_vector translation = {0, 0, 0};
    t_color   color = {0,0,0};
    float rot_speed = 0.1;
    float trans_speed = 0.5;
    float d_h = 0;
    switch (key) {
        // Rotation
        case 65362: rotation.x = rot_speed; break;  // Up arrow
        case 65364: rotation.x = -rot_speed; break; // Down arrow
        case 65361: rotation.y = rot_speed; break;  // Left arrow
        case 65363: rotation.y = -rot_speed; break; // Right arrow
        case 113:   rotation.z = rot_speed; break;  // 'q' key
        case 101:   rotation.z = -rot_speed; break; // 'e' key
        
        // Translation
        case 119: translation.z = trans_speed; break;  // 'w' key
        case 115: translation.z = -trans_speed; break; // 's' key
        case 97:  translation.x = -trans_speed; break; // 'a' key
        case 100: translation.x = trans_speed; break;  // 'd' key
        case 122: translation.y = trans_speed; break;  // 'z' key
        case 120: translation.y = -trans_speed; break; // 'x' key

        case 'r': color.r++; break; // 'r' key
        case 'g': color.g++; break; // 'g' key
        case 'b': color.b++; break; // 'b' key

        case 61: d_h = 0.5; break;
        case '-': d_h = -0.5; break;
    }
    if (d_h != 0)
        ft_resize_unique_property(scene, 0, d_h);
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0 ||
        translation.x != 0 || translation.y != 0 || translation.z != 0 || color.r || color.g || color.b) {
        transform_scene(scene, rotation, translation, color);
    }
    return (0);
}
int mouse_hook(int button, int x, int y, t_mlx_data *data) {
    float d_r = 0;
    // printf("Mouse button %d clicked at (%d, %d)\n", button, x, y);
    if (button == 1) data->mouse.is_left_pressed = 1;
    if (button == 3) data->mouse.is_right_pressed = 1;
    if (button == 4 || button == 5)
    {
        if (button == 4)
            d_r = 0.5;
        else
            d_r = -0.5;
        ft_resize_unique_property(data->scene, d_r, 0);
    }
    data->mouse.last_x = x;
    data->mouse.last_y = y;
    if (button == 1)
    {
        t_ray ray = ft_generate_ray(x, y, data->scene);
        t_intersection *inter = ft_get_nearest_intersection(&ray, data->scene);
        if (inter)
        {
            (data->scene->selected_object).type = inter->object_type;
            (data->scene->selected_object).shape = inter->object;
            free(inter);
        }
    }
    data->redraw_needed = 1;
    return 0;
}

int mouse_release(int button, int x, int y, t_mlx_data *data) {
    (void)x;
    (void)y;
    if (button == 1) data->mouse.is_left_pressed = 0;
    if (button == 3) data->mouse.is_right_pressed = 0;
    return 0;
}

int loop_hook(t_mlx_data *data) {
    if (data->redraw_needed) {
        render_scene(data->scene, data);
        mlx_put_image_to_window(data->mlx_connection, data->mlx_window, data->image.img_ptr, 0, 0);
        data->redraw_needed = 0;  // Reset the redraw flag
    }
    return 0;
}




int ft_close(t_mlx_data *data)
{
    // Add these cleanup calls:
    if (data->mlx_connection)
    {
        if (data->image.img_ptr)
            mlx_destroy_image(data->mlx_connection, data->image.img_ptr);   
        if (data->mlx_window)
            mlx_destroy_window(data->mlx_connection, data->mlx_window);
        mlx_destroy_display(data->mlx_connection);  // Add this
        free(data->mlx_connection);                 // Add this
    }
    clear_scene(data->scene);
    exit(0);  // Clean exit
    return (0);
}
t_vector get_object_position(t_object *object){
     switch (object->type) {
        case SPH: {
            t_sphere *sphere = (t_sphere *)object->shape;
            return(sphere->center);
            break;
        }
        case CYL: {
            t_cylinder *cylinder = (t_cylinder *)object->shape;
            return(cylinder->center);
            break;
        }
        case PLN: {
            t_plane *plane = (t_plane *)object->shape;
            return(plane->point);
            break;
        }
        case CONE:
        {
            t_cone *cone = (t_cone *)object->shape;
            return(cone->center);
            break;
        }
        default:
           break;;
    }
    return (t_vector){0, 0, 0};

}
t_vector get_world_space_translation(t_mlx_data *data, t_camera *camera, int dx, int dy) {
   // Calculate the change in world coordinates for mouse movement
   float view_distance = 1.0f;  // Distance to view plane
   float view_height = 2.0f * view_distance * tanf(camera->fov * 0.5f * 3.14f / 180.0f);
   float view_width = view_height * camera->aspect_ratio;
   
   // Convert pixel delta to world space delta
   float world_dx = (dx * view_width) / WIDTH;  
   float world_dy = -(dy * view_height) / HEIGHT; // Negate for correct direction

   // Transform to camera space vectors
   t_vector translation = vector_add(
       vector_multiply(camera->right, world_dx),
       vector_multiply(camera->up, world_dy)
   );
   
   // Scale based on camera's orientation
   float distance_scale = 1.0f;
   if (data->scene->selected_object.type != NONE) {
       t_vector obj_pos = get_object_position(&data->scene->selected_object);
       float dist = fabsf(vector_dot_product(
           vector_subtract(obj_pos, camera->position),
           camera->forward
       ));
       distance_scale = dist / view_distance;
   }
   
   return vector_multiply(translation, distance_scale);
}

int mouse_move(int x, int y, t_mlx_data *data) {
    if (data && (data->mouse.is_left_pressed || data->mouse.is_right_pressed)) {
        int dx = x - data->mouse.last_x;
        int dy = y - data->mouse.last_y;
        
        
        t_vector translation = get_world_space_translation(data, &data->scene->camera, dx, dy);
        
        // Apply translation to the selected object or camera
        if (data->mouse.is_left_pressed)
            transform_scene(data->scene, (t_vector){0, 0, 0}, translation, (t_color){0, 0, 0});
        data->redraw_needed = 1;
    }
    
    data->mouse.last_x = x;
    data->mouse.last_y = y;
    return 0;
}
