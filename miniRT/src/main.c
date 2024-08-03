#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define WIDTH 640
#define HEIGHT 480

typedef struct s_image {
    void *img_ptr;
    char *img_pixel_ptr;
    int bits_per_pixel;
    int endian;
    int line_len;
} t_img;

typedef struct s_mlx_data {
    void *mlx_connection;
    void *mlx_window;
    t_img image;
    int frame;
} t_mlx_data;

void my_pixel_put(t_img *img, int x, int y, int color)
{
    int offset;

    offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
    *((unsigned int *)(offset + img->img_pixel_ptr)) = color;
}

void draw_frame(t_mlx_data *data)
{
    int x, y;
    float time = data->frame * 0.1; // Use frame count for smooth animation

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            // Animated square
            if (fabs(x - (WIDTH/2 + sin(time) * 100)) < 20 && 
                fabs(y - (HEIGHT/2 + cos(time) * 100)) < 20) {
                my_pixel_put(&(data->image), x, y, GREEN);
            }
            // Animated circle
            else if (((x - WIDTH/2) * (x - WIDTH/2) + 
                      (y - HEIGHT/2) * (y - HEIGHT/2)) < 
                     (100 + 50 * sin(time))) {
                my_pixel_put(&(data->image), x, y, RED);
            }
            else {
                my_pixel_put(&(data->image), x, y, BLACK);
            }
        }
    }
}

int animation_loop(t_mlx_data *data)
{
    data->frame++;
    draw_frame(data);
    mlx_put_image_to_window(data->mlx_connection, data->mlx_window, data->image.img_ptr, 0, 0);
    return 0;
}

int key_hook(int keycode, t_mlx_data *data)
{
    if (keycode == 53) // ESC key
    {
        mlx_destroy_window(data->mlx_connection, data->mlx_window);
        exit(0);
    }
    return 0;
}

int main(void)
{
    t_mlx_data data;

    data.mlx_connection = mlx_init();
    if (!data.mlx_connection)
        return -1;

    data.mlx_window = mlx_new_window(data.mlx_connection, WIDTH, HEIGHT, "Animated Mini Ray Tracer");
    if (!data.mlx_window)
    {
        free(data.mlx_connection);
        return -1;
    }

    data.image.img_ptr = mlx_new_image(data.mlx_connection, WIDTH, HEIGHT);
    data.image.img_pixel_ptr = mlx_get_data_addr(data.image.img_ptr, 
                                                 &data.image.bits_per_pixel, 
                                                 &data.image.line_len, 
                                                 &data.image.endian);

    data.frame = 0;

    mlx_loop_hook(data.mlx_connection, animation_loop, &data);
    mlx_key_hook(data.mlx_window, key_hook, &data);

    mlx_loop(data.mlx_connection);

    return 0;
}