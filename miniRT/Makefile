CC = cc
CFLAGS = #-Wall -Werror -Wextra
LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a
MLX_DYLIB = $(MLX_DIR)/libmlx.dylib

SRC_DIR = src
SRC_FILES = main.c \
            # Add other source files here

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:.c=.o)

NAME = minirt

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX) $(MLX_DYLIB)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx \
		-framework OpenGL -framework AppKit \
		-Wl,-rpath,@executable_path/$(MLX_DIR) \
		-o $(NAME)
	cp $(MLX_DYLIB) .

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX) $(MLX_DYLIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) libmlx.dylib
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re