# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/28 19:34:56 by mhurd             #+#    #+#              #
#    Updated: 2017/03/05 14:48:40 by mhurd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= RT

SRC		= main.c \
		  parser.c \
		  renderer.c \
		  raytracer.c \
		  hooks.c \
		  error.c \
		  color_point.c \
		  parse_basic.c \
		  parse_light.c \
		  parse_extras.c \
		  parse_shapes.c \
		  parse_model.c \
		  intersect_sphere.c \
		  intersect_cylinder.c \
		  intersect_plane.c \
		  intersect_cone.c \
		  intersect_model.c \
		  helpers.c \
		  post.c \
		  handle_trans.c \
		  manip_colors.c \
		  ssaa.c \
		  perlin.c \
		  update_model.c \
			progress.c \
		  /user_input/user_input.c \
		  /user_input/print_objects.c \
		  /user_input/print_model.c \
		  /user_input/print_scene.c \
		  /user_input/parse_misc.c \
		  /user_input/modify_object.c \
		  /user_input/add_object.c \
		  /user_input/set_props.c \

ifdef ALLOCWRAP
	LDFLAGS += $(HOME)/lib/alloc_wrap.c -ldl
endif
OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O3 -march=native -funroll-loops

LIBFT	= ./libft/libft.a
LIBINC	= -I./libft
LIBLINK	= -L./libft -lft

MLX		= ./minilibx/libmlx.a
MLXINC	= -I./minilibx
MLXLINK	= -L./minilibx -lmlx -framework OpenGL -framework AppKit

LIBGFX		= ./libgfx/libgfx.a
LIBGFXINC	= -I./libgfx
LIBGFXLINK	= -L./libgfx -lgfx

SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/
OBJDIR2	= ./obj/user_input/

all: obj libft mlx libgfx $(NAME)

gfx:
	rm -rf $(NAME)
	rm -rf $(OBJDIR)
	make -C ./libgfx fclean
	make

obj:
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR2)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(LIBINC) $(MLXINC) $(LIBGFXINC) -I $(INCDIR) -o $@ -c $<

libft: $(LIBFT)

mlx: $(MLX)

libgfx: $(LIBGFX)

$(LIBFT):
	make -C ./libft

$(MLX):
	make -C ./minilibx

$(LIBGFX):
	make -C ./libgfx

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJ) $(MLXLINK) $(LIBGFXLINK) $(LIBLINK)

clean:
	rm -rf $(OBJDIR)
	make -C ./libft clean
	make -C ./minilibx clean
	make -C ./libgfx clean

nm: all
	nm -U RT 2>/dev/null | grep -ve '^[[:space:]]*$' | grep -v ':'|  sed -E 's/^_//' | tr "\t" " " | sed 's/.* //'

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean
	make -C ./libgfx fclean

re: fclean all
