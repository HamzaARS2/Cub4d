CFLAGS = 
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit

MLX := ~/MLX42
MLX_BUILD := $(MLX)/build
MLX_LIB = $(MLX)/build/libmlx42.a -Iinclude -lglfw

LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

HEADERS := $(MLX)/include

GNL_FILES := gnl/get_next_line.c gnl/get_next_line_utils.c
MAIN_FILES = cub4d.c mapscan/mapscan.c mapscan/mp_reader.c $(GNL_FILES)


OBJS_FILES = $(MAIN_FILES:.c=.o)

NAME = cub3D

all: libmlx $(NAME)

libmlx:
	@cmake $(MLX) -B $(MLX_BUILD)
	@make -C $(MLX_BUILD) -j4

$(LIBFT):
	@make -C $(LIBFT_DIR) all bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_FILES) $(LIBFT) $(MLX_LIB) -o $@

clean:
	rm -rf $(OBJS_FILES)
	rm -rf $(MLX_BUILD)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@make -C $(LIBFT_DIR)  fclean

re: fclean all