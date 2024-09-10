/**
 * @file main.c
 * @brief Main file for the miniRT ray tracing project.
 */

#include "../include/miniRT.h"


int main(int argc, char *argv[]) {
    t_mlx_data data;
    t_scene scene;

     if (argc != 2)
    {
        ft_putstr_fd("Error\nUsage: ./miniRT scene_file.rt\n", 2);
        return (1);
    }

    // Initialize scene
    scene.spheres = malloc(sizeof(t_list *));
    scene.planes = malloc(sizeof(t_list *));
    scene.cylinders = malloc(sizeof(t_list *));
    *(scene.spheres) = NULL;
    *(scene.planes) = NULL;
    *(scene.cylinders) = NULL;

    if (!parse_scene(argv[1], &scene))
    {
        ft_putstr_fd("Error\nInvalid scene file\n", 2);
        // Free any allocated memory in scene
        return (1);
    }
    //ft_scene_init(&scene);
    data.scene = &scene;
    if (!mlx_data_init(&data)) {
        fprintf(stderr, "Failed to initialize MLX data\n");
        return 1;
    }
    
    ft_setup_camera(&(scene.camera));
    
    render_scene(&scene, &data);
    mlx_put_image_to_window(data.mlx_connection, data.mlx_window, data.image.img_ptr, 0, 0);

    mlx_loop(data.mlx_connection);

    return 0;
}

void my_pixel_put(t_img *img, int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    int offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
    *((unsigned int *)(img->img_pixel_ptr + offset)) = color;
}




int key_hook(int keycode, t_mlx_data *data)
{
    if (keycode == 53) {  // ESC key
        mlx_destroy_window(data->mlx_connection, data->mlx_window);
        exit(0);
    }
    return 0;
}

int mlx_data_init(t_mlx_data *data)
{
    data->mlx_connection = mlx_init();
    if (!data->mlx_connection) return 0;

    data->mlx_window = mlx_new_window(data->mlx_connection, WIDTH, HEIGHT, "Ray Tracer");
    if (!data->mlx_window) {
        free(data->mlx_connection);
        return 0;
    }

    data->image.img_ptr = mlx_new_image(data->mlx_connection, WIDTH, HEIGHT);
    if (!data->image.img_ptr) {
        mlx_destroy_window(data->mlx_connection, data->mlx_window);
        free(data->mlx_connection);
        return 0;
    }

    data->image.img_pixel_ptr = mlx_get_data_addr(data->image.img_ptr,
                                                 &data->image.bits_per_pixel,
                                                 &data->image.line_len,
                                                 &data->image.endian);
    data->frame = 0;
    return 1;
}




void render_scene(t_scene *scene, t_mlx_data *data)
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            t_ray ray = ft_generate_ray(x, y, scene);
            t_color color = trace_ray(&ray, scene, MAX_DEPTH);
            my_pixel_put(&(data->image), x, y, color_to_int(color));
        }
    }
}