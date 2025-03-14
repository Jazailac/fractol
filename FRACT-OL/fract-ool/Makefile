# Project Name
NAME = fractol

# Source Files
SRC = main.c \
      utils.c \
      fractol.c

# Object Files
OBJ = $(SRC:.c=.o)

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./minilibx  
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Default Target
all: $(NAME)

# Linking the Final Executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

# Compiling Source Files into Object Files
%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

# Cleaning Up Object Files
clean:
	rm -f $(OBJ)

# Cleaning Up Everything (Objects and Executable)
fclean: clean
	rm -f $(NAME)

# Rebuild the Project
re: fclean all

# Phony Targets
.PHONY: all clean fclean re