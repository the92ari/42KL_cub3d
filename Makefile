# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 17:03:19 by kwang             #+#    #+#              #
#    Updated: 2022/09/25 22:57:14 by kwang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/main.c \
		src/error_handler \
		src/file_validator \
		src/config_handler \

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES) -I/usr/include/ -Imlx_linux -O3

MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

INCLUDES = includes

LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a

MLX = mlx_linux/libmlx_Linux.a

NAME = cub3d

all : $(NAME)

$(LIBFT) :
	@git submodule init
	@git submodule update
	@make -C $(LIBFTDIR) all

$(MLX) :
	@git submodule init
	@git submodule update
	@make -C mlx_linux

$(NAME) : $(OBJS) $(INCLUDES)/$(NAME).h $(LIBFT) $(MLX)
	@echo "Creating $(NAME).."
	@echo "Your display variable is $$DISPLAY"
	@$(CC) $(CFLAGS) -o $@ $^ $(MLXFLAGS)

bonus : ${NAME}

clean :
	@echo "Cleaning all .o files.."
	@make -C mlx_linux clean
	@make -C $(LIBFTDIR) clean
	@rm -f $(OBJS)

fclean : clean
	@echo "Cleaning $(NAME)"
	@make -C $(LIBFTDIR) fclean
	@rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
