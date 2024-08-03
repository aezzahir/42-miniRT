#include <mlx.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define WIDTH 540
#define HEIGHT 540

void    *mlx;
void    *mlx_win;

int    my_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);

typedef struct mlx_data_struct 
{
	int        width;
    int        height;
    char    *title;
	void	*mlx_connection;
	void    *mlx_window;
} t_mlx_data;
int	main(void)
{
	t_mlx_data data;
	data.width = 640;
	data.height = 480;
	data.title = "Mini Ray Tracer";

	data.mlx_connection = mlx_init(); // establish connection with mlx Server
	if (!data.mlx_connection)
		return -1;
	
	data.mlx_window = mlx_new_window(data.mlx_connection, data.height, data.width, data.title); // create window
	if (!data.mlx_window)
	{
		// mlx_destroy_display(mlx_connection); //TODO: destroy
		free(data.mlx_connection);
		return -1;
	}
	mlx_loop(data.mlx_connection);

	return 0; 
}
