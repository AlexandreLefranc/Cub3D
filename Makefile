#------------------------------------------------------------------------------#
#                                                                              #
#                               DECLARATIONS                                   #
#                                                                              #
#------------------------------------------------------------------------------#

#------------------------------------#
#             COMPILATION            #
#------------------------------------#

NAME	=	cub3d

CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -g3
INC		=	-I include

#------------------------------------#
#                LIBFT               #
#------------------------------------#

LIBFT_DIR	=	libft/
LIBFT_A		=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	-I $(LIBFT_DIR)include
LIBFT_LD	=	-lft -L $(LIBFT_DIR)

#------------------------------------#
#              MINILIBX              #
#------------------------------------#

MLX_DIR	=	minilibx/
MLX_A	=	$(MLX_DIR)libmlx.a
MLX_INC	=	-I $(MLX_DIR)
MLX_LD	=	-lmlx -lXext -lX11 -L $(MLX_DIR)

#------------------------------------#
#               SOURCES              #
#------------------------------------#

SRC_DIR		=	testLouiseA/
SRC_FILES	=	main.c
				# init.c \
				# parser.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

#------------------------------------#
#               OBJECTS              #
#------------------------------------#

OBJ_DIR	= 	obj/
OBJ		=	$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC:.c=.o))

#------------------------------------#
#              INCLUDES              #
#------------------------------------#

HEADER = include/cub3d.h

#------------------------------------#
#              SUMMARY               #
#------------------------------------#

INC_FLAGS	=	$(INC) $(LIBFT_INC) $(MLX_INC)
LD_FLAGS	=	$(LIBFT_LD) $(MLX_LD)

#------------------------------------------------------------------------------#
#                                                                              #
#                                   RULES                                      #
#                                                                              #
#------------------------------------------------------------------------------#

all: $(NAME)
	@echo "\033[0;32mProgram $(NAME) created !\033[0m"

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJ)
	@echo "\033[0;36mLinking objects !\033[0m"
	$(CC) $(CFLAGS) $(OBJ) $(INC_FLAGS) $(LD_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)

$(LIBFT_A):
	make -C $(LIBFT_DIR)

$(MLX_A):
	make -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
