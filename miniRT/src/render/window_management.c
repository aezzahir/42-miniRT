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
    printf("key released --> %d\n", keycode);
    if (keycode == 65307) {  // ESC key
        ft_close(data);
    }
    if (keycode == 'c') {
        data->scene->selected_object.type = CAM;
    }
    if (keycode == 'l') {
        data->scene->selected_object.type = LIGHT;
        data->scene->selected_object.shape = &(data->scene->light);
        printf("Light's position: ");
        vector_print(data->scene->light.position);
    }
    if (keycode == 'r') {
        data->redraw_needed = 1;
    }
    
    // Handle transformations
    handle_user_input(data->scene, keycode);
    
    // Set redraw flag after any transformation
    data->redraw_needed = 1;
    
    return 0;
}

void handle_user_input(t_scene *scene, int key) {
    t_vector rotation = {0, 0, 0};
    t_vector translation = {0, 0, 0};
    float rot_speed = 0.1;
    float trans_speed = 0.5;
    float d_r = 0;
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

        // Resizing 
        case 61: d_r = 0.5; break;
        case '-': d_r = -0.5; break;
        case 'h': d_h = 0.5; break;
        case 'j': d_h = -0.5; break;
    }
    if (d_r != 0 || d_h != 0)
        ft_resize_unique_property(scene, d_r, d_h);
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0 ||
        translation.x != 0 || translation.y != 0 || translation.z != 0) {
        transform_scene(scene, rotation, translation);
    }
}
int mouse_hook(int button, int x, int y, t_mlx_data *data) {
    printf("Mouse button %d clicked at (%d, %d)\n", button, x, y);
    if (button == 1)
    {
        t_ray ray = ft_generate_ray(x, y, data->scene);
        t_intersection *inter = ft_find_nearest_intersection(&ray, data->scene);
        if (inter)
        {
            (data->scene->selected_object).type = inter->object_type;
            (data->scene->selected_object).shape = inter->object;
        }
        if ((data->scene->selected_object).type == SPH)
            printf("Wahoooh you selected a SPHERE\n");
    }
    data->redraw_needed = 1;
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