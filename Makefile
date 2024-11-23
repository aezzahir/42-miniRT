# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 22:13:36 by iben-haj          #+#    #+#              #
#    Updated: 2024/11/23 11:18:33 by iben-haj         ###   ########.fr        #
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
			clean_up_helper.c \
			parse/config_reader.c \
			parse/atof.c \
			parse/next_line.c \
			parse/parse_light.c \
			parse/parse_shapes.c \
            geometry/vector.c   \
            geometry/vector1.c   \
            geometry/vector2.c   \
            geometry/vector3.c   \
			geometry/plane.c \
            geometry/sphere.c   \
			geometry/cone.c  \
			geometry/cylinder.c \
			geometry/cylinder_1.c \
			render/raytracer.c   \
            render/camera.c     \
			render/lighting.c \
			render/transformations.c \
			render/color.c \
			render/window_management.c \
			utils/rotate.c \
			utils/rotate_helper.c \
			utils/nearest_intersection.c \
			utils/nearest_intersection1.c \
			utils/hooks.c \
			utils/hooks_helper.c \
			utils/rays.c \
			utils/anti_alias.c \
			utils/mouse.c \
			utils/helpers.c \
			utils/helpers1.c \

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