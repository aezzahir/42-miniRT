# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 22:13:36 by iben-haj          #+#    #+#              #
#    Updated: 2024/11/20 22:13:37 by iben-haj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra 
LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = lib/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

SRC_DIR = src
SRC_FILES = main.c \
			clean_up.c \
			parse/config_reader.c \
            geometry/vector.c   \
			geometry/plane.c \
            geometry/sphere.c   \
			geometry/cone.c  \
			geometry/cylinder.c \
			render/raytracer.c   \
            render/camera.c     \
			render/lighting.c \
			render/transformations.c \
			render/color.c \
			render/window_management.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:.c=.o)

NAME = minirt

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux \
		-L/usr/lib -lXext -lX11 -lm -lz \
		-o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -I/usr/include -O3 -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re