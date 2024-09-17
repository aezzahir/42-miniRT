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
    // free all alocated memories
    mlx_destroy_window(data->mlx_connection, data->mlx_window);
    exit(0);
    return (0);
}

t_vector get_world_space_translation(t_camera *camera, int dx, int dy, float sensitivity) {
    // Get the camera's right vector (perpendicular to up and direction)
    t_vector right = vector_cross_product(camera->orientation, camera->up);
    right = vector_normalize(right);

    // Scale the movement based on sensitivity
    float scaled_dx = dx * sensitivity;
    float scaled_dy = dy * sensitivity;

    // Calculate the world space movement
    t_vector horizontal_movement = vector_multiply(right, scaled_dx);
    t_vector vertical_movement = vector_multiply(camera->up, -scaled_dy);

    // Combine the movements
    return vector_add(horizontal_movement, vertical_movement);
}

int mouse_move(int x, int y, t_mlx_data *data) {
    if (data->mouse.is_left_pressed || data->mouse.is_right_pressed) {
        int dx = x - data->mouse.last_x;
        int dy = y - data->mouse.last_y;
        
        float sensitivity = 0.11f; // Adjust this value to change movement speed
        
        t_vector translation = get_world_space_translation(&data->scene->camera, dx, dy, sensitivity);
        
        // Apply translation to the selected object or camera
        if (data->mouse.is_left_pressed)
            transform_scene(data->scene, (t_vector){0, 0, 0}, translation, (t_color){0, 0, 0});
        data->redraw_needed = 1;
    }
    
    data->mouse.last_x = x;
    data->mouse.last_y = y;
    return 0;
}