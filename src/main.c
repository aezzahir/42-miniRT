/**
 * @file main.c
 * @brief Main file for the miniRT ray tracing project with redraw functionality.
 */

#include "../include/miniRT.h"


int main(int argc, char *argv[]) {
    t_mlx_data data;
    t_scene scene;

    if (argc != 2) {
        ft_putstr_fd("Error\nUsage: ./miniRT scene_file.rt\n", 2);
        return (1);
    }

    // Initialize scene
    scene.spheres = malloc(sizeof(t_list *));
    if (!scene.spheres) {
        ft_putstr_fd("Error\nMemory allocation failed for spheres\n", 2);
        return 1;
    }
    scene.planes = malloc(sizeof(t_list *));
    if (!scene.planes) {
        ft_putstr_fd("Error\nMemory allocation failed for planes\n", 2);
        free(scene.spheres);
        return 1;
    }
    scene.cylinders = malloc(sizeof(t_list *));
    if (!scene.cylinders) {
        ft_putstr_fd("Error\nMemory allocation failed for cylinders\n", 2);
        free(scene.planes);
        free(scene.spheres);
        return 1;
    }
    scene.cones = malloc(sizeof(t_list *));
    if (!scene.cones) {
        ft_putstr_fd("Error\nMemory allocation failed for cylinders\n", 2);
        free(scene.planes);
        free(scene.spheres);
        free(scene.cylinders);
        return 1;
    }

    *(scene.cones) = NULL;
    *(scene.spheres) = NULL;
    *(scene.planes) = NULL;
    *(scene.cylinders) = NULL;

    if (!parse_scene(argv[1], &scene)) {
        ft_putstr_fd("Error\nInvalid scene file\n", 2);
        // Free any allocated memory in scene
        return (1);
    }

    data.scene = &scene;
    data.mouse.is_left_pressed = 0;
    data.mouse.is_right_pressed = 0;
    data.mouse.last_x = 0;
    data.mouse.last_y = 0;
    if (!mlx_data_init(&data)) {
        fprintf(stderr, "Failed to initialize MLX data\n");
        return 1;
    }
    
    ft_setup_camera(&(scene.camera));

   // Set up MiniLibX hooks
    mlx_expose_hook(data.mlx_window, expose_hook, &data);
    mlx_key_hook(data.mlx_window, key_hook, &data);
    mlx_mouse_hook(data.mlx_window, mouse_hook, &data);
    mlx_hook(data.mlx_window, 17, 1L<<17, ft_close, &data);
    mlx_loop_hook(data.mlx_connection, loop_hook, &data);
    mlx_hook(data.mlx_window, 2, 1L<<0, key_press, &data);



     // Set up MiniLibX hooks
    mlx_hook(data.mlx_window, 5, 1L<<3, mouse_release, &data); // Mouse release
    mlx_hook(data.mlx_window, 6, 1L<<6, mouse_move, &data);
    // Initial render
    render_scene(&scene, &data);
    mlx_put_image_to_window(data.mlx_connection, data.mlx_window, data.image.img_ptr, 0, 0);

    mlx_loop(data.mlx_connection);
   
    clear_scene(&scene);
    return 0;
}



int mlx_data_init(t_mlx_data *data) {
    data->width = WIDTH;
    data->height = HEIGHT;
    data->mlx_connection = mlx_init();
    if (!data->mlx_connection) return 0;

    data->mlx_window = mlx_new_window(data->mlx_connection, data->width, data->height, "miniRT");
    if (!data->mlx_window) {
        free(data->mlx_connection);
        return 0;
    }

    data->image.img_ptr = mlx_new_image(data->mlx_connection, data->width, data->height);
    if (!data->image.img_ptr) {
        mlx_destroy_window(data->mlx_connection, data->mlx_window);
        free(data->mlx_connection);
        return 0;
    }

    data->image.img_pixel_ptr = mlx_get_data_addr(data->image.img_ptr,
                                                 &data->image.bits_per_pixel,
                                                 &data->image.line_len,
                                                 &data->image.endian);
    data->redraw_needed = 1;  // Set initial redraw flag
    return 1;
}
