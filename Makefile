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
CFLAGS	=	-Wall -Wextra -Werror -g3 # -Wno-error=unused-function
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

SRC_DIR		=	src/
<<<<<<< HEAD
SRC_FILES	=	main.c \
				check_rgb.c \
				create_texture.c \
				create_window.c \
				display_minimap.c \
				init.c \
				map_modeler.c \
				parser.c \
				parser_info.c \
				parser_map.c \
				utils.c
=======
SRC_FILES	=	main_map_modeler.c \
				map_modeler.c
				# main.c \
				# init.c \
				# parser.c
>>>>>>> e0b11ede0d4bdf5fe641ba321d392752521ab7d1

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

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJ)
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
