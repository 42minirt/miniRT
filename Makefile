#####################################################
# COMPILE ###########################################
#####################################################
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -MMD -MP

ifdef WITH_LEAKS
	CFLAGS 		+= -D LEAKS
endif

ifdef WITH_SANITIZE
	CFLAGS 		+= -g -fsanitize=address
endif


#####################################################
# PROGRAM NAME ######################################
#####################################################
NAME			= miniRT


#####################################################
# SRC FILE ##########################################
#####################################################
VPATH			= $(SRC_DIR) $(INCLUDE_DIR)

SRC_DIR			= srcs
SRC				= main.c
SRCS			= $(addprefix $(SRC_DIR)/, $(SRC))

#----------------------------------------------------
# CONSTRUCTOR
CONSTRUCTOR_DIR	= srcs/constructor
CONSTRUCTOR_SRC	= constructor.c \
				  ft_strtod.c \
				  ft_strtol.c \
				  get_config.c \
				  get_config_of_ambient.c \
				  get_config_of_camera.c \
				  get_config_of_each_obj.c \
				  get_config_of_lights.c \
				  get_config_of_objects.c \
				  get_image_data_from_ppm.c \
				  get_image_texture.c \
				  get_bonus_config_of_obj.c \
				  parsing_config.c \
				  parsing_digits.c \
				  parsing_helper.c \
				  parsing_id_cnt.c \
				  parsing_ppm.c \
				  parsing_ppm_each_line.c \
				  update_camera_config.c \
				  update_scene_config.c \
				  update_scene_config_each_obj.c \
				  update_scene_config_light.c \
				  validate_config.c \
				  validate_config_color.c \
				  validate_config_shape.c \
				  validate_config_light.c \
				  validate_filename.c \
				  validate_is.c

SRC				+= $(addprefix $(CONSTRUCTOR_DIR)/, $(CONSTRUCTOR_SRC))

#----------------------------------------------------
# DESTRUCTOR
DESTRUCTOR_DIR	= srcs/destructor
DESTRUCTOR_SRC	= destructor.c

SRC				+= $(addprefix $(DESTRUCTOR_DIR)/, $(DESTRUCTOR_SRC))

#----------------------------------------------------
# MLX_HELPER
MLX_HELPER		= srcs/mlx_helper
MLX_HELPER_SRS	= mlx_pixcel_put.c \
				  mlx_keyhooks.c

SRC				+= $(addprefix $(MLX_HELPER)/, $(MLX_HELPER_SRS))

#----------------------------------------------------
# RAYTRACE
RAYTRACE_DIR	= srcs/raytrace
RAYTRACE_SRC	= calc_ambient_reflection.c \
				  calc_rayvec.c \
				  calc_specular_reflection.c \
				  calc_perfect_reflection.c \
				  calc_diffuse_reflection.c \
				  calc_diffuse_reflection_param.c \
				  get_checker_ref_color.c \
				  get_image_ref_color.c \
				  get_tangent_coordinate_map.c \
				  intersection_helper.c \
				  intersection_with_corn.c \
				  intersection_with_corn_calc_param.c \
				  intersection_with_sphere.c \
				  is_condition.c \
				  raytrace.c \
				  handle_normal.c \
				  calc_ratio/calcratio_cylinder.c \
				  calc_ratio/calcratio_plane.c

SRC				+= $(addprefix $(RAYTRACE_DIR)/, $(RAYTRACE_SRC))

#----------------------------------------------------
# COLOR
COLOR_DIR		= srcs/calc_color
COLOR_SRC		= calc_color.c \
				  color_handling.c

SRC				+= $(addprefix $(COLOR_DIR)/, $(COLOR_SRC))

#----------------------------------------------------
# VECTOR
VECTOR_DIR		= srcs/calc_vector
VECTOR_SRC		= arithmetic.c \
				  arithmetic_ret_vec.c \
				  calc_vec.c \
				  organize_vec.c

SRC				+= $(addprefix $(VECTOR_DIR)/, $(VECTOR_SRC))

#----------------------------------------------------
# MATRIX
MATRIX_DIR		= srcs/matrix
MATRIX_SRC		= calc_matrix.c \
				  is_basis_equals.c \
				  matrix.c

SRC				+= $(addprefix $(MATRIX_DIR)/, $(MATRIX_SRC))

#----------------------------------------------------
# DEBUG
DEBUG_DIR		= srcs/debug
DEBUG_SRC		= print_config.c \
				  print_config_helper.c

SRC				+= $(addprefix $(DEBUG_DIR)/, $(DEBUG_SRC))

#----------------------------------------------------
# SYS
SYS_DIR			= srcs/sys
SYS_SRC			= x_free.c \
				  x_open.c \
				  x_close.c

SRC				+= $(addprefix $(SYS_DIR)/, $(SYS_SRC))


#####################################################
# OBJECT FILE #######################################
#####################################################
OBJ_DIR			= objs
OBJ				= $(SRC:%.c=%.o)
OBJS			= $(addprefix $(OBJ_DIR)/, $(OBJ))
DEPS			= $(SRCS:%.c=%:d)



#####################################################
# OS Check ##########################################
#####################################################
UNAME			= $(shell uname)


#####################################################
# INCLUDE and LIBRARY FILE ##########################
#####################################################

# ---------------------------------------------------
# LIBFT
LIBFT_DIR		= libs
LIBFT			= $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE	= $(LIBFT_DIR)/include


# ---------------------------------------------------
# MLX
MLX_DIR			= minilibx-linux


# ---------------------------------------------------
# X11
X11_DIR			= /usr/X11
X11_LIB			= /usr/X11/lib
X11_INCLUDE		= /usr/X11/include


# ---------------------------------------------------
# LIBS, LIBS_DIR ####################################
LIBS_DIR 		= $(LIBFT_DIR) $(MLX_DIR) $(X11_DIR) $(X11_LIB)

ifeq ($(UNAME), Darwin)
	LIBS_DIR 	+= /usr/X11R6/lib
endif

LFLAGS			= $(addprefix -L, $(LIBS_DIR))


ifeq ($(UNAME), Darwin)
	LIBS 		= -lft -lmlx_Darwin -lXext -lX11 -lm -framework OpenGL -framework AppKit
	CFLAGS 		+= -D LEAKS
else
	LIBS		= -lft -lmlx -lXext -lX11 -lm
endif


# ---------------------------------------------------
# INCLUDES ##########################################
MINIRT_INCLUDE	= includes
INCLUDE_DIRS	= $(MINIRT_INCLUDE) $(LIBFT_INCLUDE) $(MLX_DIR) $(X11_INCLUDE)
IFLAGS			= $(addprefix -I, $(INCLUDE_DIRS))



#####################################################
# RULES #############################################
#####################################################
all				: $(NAME)


$(NAME)			: $(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) $(LFLAGS)


$(OBJ_DIR)/%.o : %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean			:
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

fclean			: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@#make fclean -C $(MLX_DIR)

re				: fclean all

bonus			: all

leaks			:
	make re WITH_LEAKS=1

sani			:
	make all WITH_SANITIZE=1

norm			:
	@norminette --version
	norminette $(SRC_DIR) $(INCLUDE_DIR) $(LIBFT_DIR)

.PHONY			: all clean fclean re test norm bonus

-include	$(DEPS)