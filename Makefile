# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 17:03:19 by kwang             #+#    #+#              #
#    Updated: 2022/10/03 16:26:24 by kwang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/main.c \
		src/error_handler.c \
		src/file_validator.c \
		src/assets_validator.c \
		src/config_parsing_utils.c \
		src/config_parser.c \
		src/mlx_handler.c \
		src/mlx_hook_functions.c \
		src/mlx_initializer.c \
		src/config_parser_helper.c \
		src/image_utils.c \
		src/map_validator.c \
		src/map_validator_utils.c \

OBJS = $(SRCS:.c=.o)

OBJSMAC = $(SRCS:.c=.o)

CC = gcc

# CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES) -I/usr/include/ -Imlx_linux -O3
CFLAGS = -I$(INCLUDES) -I/usr/include/

UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -Imlx_linux
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGS += -Imlx
    endif

LINUXMLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

MACMLXFLAGS = -lmlx -framework OpenGL -framework AppKit

INCLUDES = includes

LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a

LIBFTFLAGS = -Llibft -lft

MLX = mlx_linux/libmlx_Linux.a

NAMELINUX = cub3dlinux

NAME = cub3d

all : $(NAME)

linux:	$(NAMELINUX)

# $(OBJSMAC): 	$(SRCS)
# 				$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@ 

$(LIBFT) :
	@make -C $(LIBFTDIR) all

$(MLX) :
	@make -C mlx_linux

$(NAMELINUX) : 	$(OBJS) $(INCLUDES)/$(NAME).h $(LIBFT) $(MLX)
				@echo "Creating $(NAMELINUX).."
				@echo "Your display variable is $$DISPLAY"
				@$(CC) $(CFLAGS) -o $@ $^ $(LINUXMLXFLAGS)

$(NAME):		$(OBJS) $(INCLUDES)/$(NAME).h $(LIBFT)
				@echo "Creating $(NAME).."
				@echo "Your display variable is $$DISPLAY"
				$(CC) $(LIBFTFLAGS) $(MACMLXFLAGS) $(OBJS) -o $(NAME)

bonus : ${NAME}

clean :
	@echo "Cleaning all .o files.."
	# @make -C mlx_linux clean
	@make -C $(LIBFTDIR) clean
	@rm -f $(OBJS)

fclean : clean
	@echo "Cleaning $(NAME)"
	@make -C $(LIBFTDIR) fclean
	@rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
