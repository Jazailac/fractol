# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 03:48:12 by jazailac          #+#    #+#              #
#    Updated: 2025/03/20 03:48:13 by jazailac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
       events.c \
       fractal_utils.c \
       utils.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm

INCLUDES = -I. -I$(LIBFT_DIR) -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

%.o: %.c fractol.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus