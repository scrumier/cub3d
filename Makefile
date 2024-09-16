CC			=	cc
FLAGS		=	-MMD -MP -g3
INC_DIR		=	includes/
INC			=	$(addprefix $(INC_DIR), \
				cube3d.h \
				)
SRC_DIR		=	exec
OBJ_DIR		=	.obj
LIBFT_DIR	=	libft
NAME		=	cub3d
RM			=	rm -f
SRC_FILES	=	$(addprefix $(SRC_DIR), \
				raycast.c \
				key_handle.c \
				anti_aliasing.c \
				find_fps.c \
				move.c \
				utils.c \
				draw.c \
				mlx_utils.c \
				find_color.c \
				opti.c \
				mini_parse.c \
				rays.c \
				open_door.c \
				$(addprefix parsing/, \
					main_parser.c \
				) \
				)
OBJ_FILES	=	$(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
DEP			=	$(OBJ_FILES:.o=.d)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX = mlx_linux
    MLX_DIR = mlx_linux/
    LIBRARIES = -L$(MLX) -lmlx_Linux -Llibft -lft -L/usr/lib -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S),Darwin)
    MLX = mlx_mac
    MLX_DIR = mlx_mac/
    LIBRARIES = -L$(MLX) -lmlx -framework OpenGL -framework AppKit -L$(LIBFT_DIR) -lft -lm -lz
endif
INCLUDES	=	-I/usr/include -I$(MLX_DIR) -Ilibft/includes -I$(INC_DIR)

all: mlx libft $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile | $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ -I$(LIBFT_DIR)

$(NAME): $(OBJ_FILES) $(INC) Makefile $(OBJ_DIR)
	$(CC) $(OBJ_FILES) $(LIBRARIES) -o $@

$(OBJ_DIR):
	mkdir -p $@
	mkdir -p $(OBJ_DIR)/parsing
mlx:
	@make -C $(MLX)

libft: FORCE
	@make -C $(LIBFT_DIR)

-include $(DEP)

clean:
	$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

FORCE:

re: fclean all

.PHONY: all clean fclean re mlx libft
