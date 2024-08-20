CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -Ofast -MMD -MP -g3
LIBRARIES	=	-Lmlx_linux -lmlx_Linux -Llibft -lft -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
INCLUDES	=	-I/usr/include -Imlx_linux -Ilibft/includes -I$(INC_DIR)
INC_DIR		=	includes/
INC			=	$(addprefiX $(INC_DIR), \
				cube3d.h \
				)
SRC_DIR		=	test_exec/
OBJ_DIR		=	.obj
LIBFT_DIR	=	libft
NAME		=	cube3d
RM			=	rm -f
MLX			=	mlx_linux
SRC_FILES	=	$(addprefix $(SRC_DIR), \
				raycast.c \
				)
OBJ_FILES	=	$(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
DEP			=	$(OBJ_FILES:.o=.d)

all: mlx libft $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile | $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -O3 -c $< -o $@ -I$(LIBFT_DIR)

$(NAME): $(OBJ_FILES) $(INC) Makefile $(OBJ_DIR)
	$(CC) $(OBJ_FILES) $(LIBRARIES) -o $@

$(OBJ_DIR):
	mkdir -p $@

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