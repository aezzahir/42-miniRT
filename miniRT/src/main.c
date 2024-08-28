/**
 * @file main.c
 * @brief Main file for the miniRT ray tracing project.
 */

#include "../include/miniRT.h"



void ft_print_vector(t_vector *vector)
{
    printf("(%.2f, %.2f, %.2f)\n", vector->x, vector->y, vector->z);
}

// Function prototypes
void my_pixel_put(t_img *img, int x, int y, int color);
void draw_frame(t_mlx_data *data);
int animation_loop(t_mlx_data *data);
int key_hook(int keycode, t_mlx_data *data);
int mlx_data_init(t_mlx_data *data);
void ft_scene_init(t_scene *scene);
void ft_setup_camera(t_camera *camera);
t_ray ft_generate_ray(int x, int y, t_scene *scene);
t_color trace_ray(t_ray *ray, t_scene *scene, int depth);
int color_to_int(t_color color);
void render_scene(t_scene *scene, t_mlx_data *data);

int main(void) {
    t_mlx_data data;
    t_scene scene;

    ft_scene_init(&scene);
    data.scene = &scene;
    if (!mlx_data_init(&data)) {
        fprintf(stderr, "Failed to initialize MLX data\n");
        return 1;
    }
    
    ft_setup_camera(&scene.camera);
    
    //mlx_loop_hook(data.mlx_connection, animation_loop, &data);
    render_scene(data.scene, &data);
    mlx_put_image_to_window(data.mlx_connection, data.mlx_window, data.image.img_ptr, 0, 0);
    mlx_key_hook(data.mlx_window, key_hook, &data);

    mlx_loop(data.mlx_connection);

    return 0;
}

void my_pixel_put(t_img *img, int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    int offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
    *((unsigned int *)(img->img_pixel_ptr + offset)) = color;
}

void draw_frame(t_mlx_data *data) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            my_pixel_put(&(data->image), x, y, 0);  // Clear with black
        }
    }
    render_scene(data->scene, data);
}

int animation_loop(t_mlx_data *data) {
    data->frame++;
    draw_frame(data);
    mlx_put_image_to_window(data->mlx_connection, data->mlx_window, data->image.img_ptr, 0, 0);
    return 0;
}

int key_hook(int keycode, t_mlx_data *data) {
    if (keycode == 53) {  // ESC key
        mlx_destroy_window(data->mlx_connection, data->mlx_window);
        exit(0);
    }
    return 0;
}

int mlx_data_init(t_mlx_data *data) {
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

void ft_scene_init(t_scene *scene) {
    scene->ambient = (t_ambient){{255, 255, 255}, 0.2};
    scene->light = (t_light){{-40, 50, 0}, 0.6, {10, 0, 255}};
    scene->camera = (t_camera){{-50, 0, 20}, {1, 0, 0}, 70};
    scene->sphere = (t_sphere){{0, 0, 20.6}, 24.6, {10, 0, 255}};
}



t_ray ft_generate_ray(int x, int y, t_scene *scene) {
    float pixel_x = (2.0 * x / WIDTH - 1) * scene->camera.viewport_width / 2;
    float pixel_y = (1 - 2.0 * y / HEIGHT) * scene->camera.viewport_height / 2;
    
    t_vector direction = vector_normalize(
        vector_add(
            vector_add(
                vector_multiply(scene->camera.right, pixel_x),
                vector_multiply(scene->camera.up, pixel_y)
            ),
            scene->camera.forward
        )
    );
    t_vector origin = vector_add(scene->camera.position, vector_multiply(scene->camera.forward, 0.001));
    
    return (t_ray){origin, direction};
}

t_color trace_ray(t_ray *ray, t_scene *scene, int depth) {
    if (depth <= 0) return scene->ambient.color;
    t_intersection *intersection = intersect_sphere(ray, &(scene->sphere));
    if (!intersection) return scene->ambient.color;
    t_color color = intersection->color;
    free(intersection);
    return color;
}

int color_to_int(t_color color) {
    return ((int)color.r << 16) | ((int)color.g << 8) | (int)color.b;
}

void render_scene(t_scene *scene, t_mlx_data *data) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            t_ray ray = ft_generate_ray(x, y, scene);
            t_color color = trace_ray(&ray, scene, MAX_DEPTH);
            my_pixel_put(&(data->image), x, y, color_to_int(color));
        }
    }
}