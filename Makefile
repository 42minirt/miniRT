#####################################################
# COMPILE ###########################################
#####################################################
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -MMD -MP
CPPFLAGS		= $(addprefix -I, $(INCLUDE_DIRS))

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
VPATH			= $(SRC_DIR) $(MINIRT_INCLUDE)

SRC_DIR			= srcs
SRC				= main.c
SRCS			= $(addprefix $(SRC_DIR)/, $(SRC))

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
				  organize_vec.c \
				  organize_vec_2.c

SRC				+= $(addprefix $(VECTOR_DIR)/, $(VECTOR_SRC))

#----------------------------------------------------
# CONSTRUCTOR
CONSTRUCTOR_DIR	= srcs/constructor
CONSTRUCTOR_SRC	= parse/ft_strtod.c \
				  parse/ft_strtol.c \
				  parse/get_bonus_config_of_obj.c \
				  parse/get_config.c \
				  parse/get_config_of_ambient.c \
				  parse/get_config_of_camera.c \
				  parse/get_config_of_each_obj.c \
				  parse/get_config_of_lights.c \
				  parse/get_config_of_objects.c \
				  parse/get_image_data_from_ppm.c \
				  parse/get_image_texture.c \
				  parse/parsing_config.c \
				  parse/parsing_digits.c \
				  parse/parsing_helper.c \
				  parse/parsing_id_cnt.c \
				  parse/parsing_ppm.c \
				  parse/parsing_ppm_each_line.c \
				  update/update_camera_config.c \
				  update/update_scene_config.c \
				  update/update_scene_config_each_obj.c \
				  update/update_scene_config_light.c \
				  validate/validate_config.c \
				  validate/validate_config_color.c \
				  validate/validate_config_light.c \
				  validate/validate_config_shape.c \
				  validate/validate_filename.c \
				  validate/validate_is_num.c \
				  validate/validate_is_struct.c \
				  constructor.c

SRC				+= $(addprefix $(CONSTRUCTOR_DIR)/, $(CONSTRUCTOR_SRC))

#----------------------------------------------------
# DEBUG
DEBUG_DIR		= srcs/debug
DEBUG_SRC		= print_config.c \
				  print_config_helper.c

SRC				+= $(addprefix $(DEBUG_DIR)/, $(DEBUG_SRC))

#----------------------------------------------------
# DESTRUCTOR
DESTRUCTOR_DIR	= srcs/destructor
DESTRUCTOR_SRC	= destructor.c

SRC				+= $(addprefix $(DESTRUCTOR_DIR)/, $(DESTRUCTOR_SRC))

#----------------------------------------------------
# DRAW
DRAW_DIR		= srcs/draw
DRAW_SRC		= draw.c

SRC				+= $(addprefix $(DRAW_DIR)/, $(DRAW_SRC))

#----------------------------------------------------
# MATRIX
MATRIX_DIR		= srcs/matrix
MATRIX_SRC		= calc_matrix.c \
				  is_basis_equals.c \
				  matrix.c

SRC				+= $(addprefix $(MATRIX_DIR)/, $(MATRIX_SRC))

#----------------------------------------------------
# MLX_HELPER
MLX_HELPER		= srcs/mlx_helper
MLX_HELPER_SRC	= mlx_pixcel_put.c \
				  mlx_keyhooks.c \
				  mlx_put_image.c

SRC				+= $(addprefix $(MLX_HELPER)/, $(MLX_HELPER_SRC))

#----------------------------------------------------
# MLX_HELPER
PRE_CHECK		= srcs/pre_check_conflict
PRE_CHECK_SRC	= conflict_ch.c \
				  conflict_ch_obj.c

SRC				+= $(addprefix $(PRE_CHECK)/, $(PRE_CHECK_SRC))

#----------------------------------------------------
# RAYTRACE
RAYTRACE_DIR	= srcs/raytrace
RAYTRACE_SRC	= calc_intersection/calcratio_cylinder.c \
				  calc_intersection/calcratio_cylinder_helper.c \
				  calc_intersection/calcratio_plane.c \
				  calc_intersection/intersection_helper.c \
				  calc_intersection/intersection_with_corn.c \
				  calc_intersection/intersection_with_corn_calc_param.c \
				  calc_intersection/intersection_with_sphere.c \
				  calc_reflection/calc_ambient_reflection.c \
				  calc_reflection/calc_diffuse_reflection.c \
				  calc_reflection/calc_diffuse_reflection_param.c \
				  calc_reflection/calc_perfect_reflection.c \
				  calc_reflection/calc_rayvec.c \
				  calc_reflection/calc_specular_reflection.c \
				  calc_reflection/get_checker_ref_color.c \
				  calc_reflection/get_image_ref_color.c \
				  calc_reflection/get_tangent_coordinate_map.c \
				  calc_reflection/handle_normal.c \
				  calc_reflection/is_condition.c \
				  raytrace.c

SRC				+= $(addprefix $(RAYTRACE_DIR)/, $(RAYTRACE_SRC))

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
DEPS			= $(OBJS:%.o=%.d)



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
#	CFLAGS 		+= -D LEAKS
else
	LIBS		= -lft -lmlx -lXext -lX11 -lm
endif


# ---------------------------------------------------
# INCLUDES ##########################################
MINIRT_INCLUDE	= includes
INCLUDE_DIRS	= $(MINIRT_INCLUDE) $(LIBFT_INCLUDE) $(MLX_DIR) $(X11_INCLUDE)



#####################################################
# RULES #############################################
#####################################################
.PHONY			: all
all				: $(NAME)


$(NAME)			: $(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LIBS) $(LFLAGS)


$(OBJ_DIR)/%.o : %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY			: clean
clean			:
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

.PHONY			: fclean
fclean			: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@#make fclean -C $(MLX_DIR)

.PHONY			: re
re				: fclean all

.PHONY			: bonus
bonus			: all

.PHONY			: leaks
leaks			:
	make re WITH_LEAKS=1

.PHONY			: sani
sani			:
	make all WITH_SANITIZE=1

.PHONY			: norm
norm			:
	@norminette --version
	norminette $(SRC_DIR) $(MINIRT_INCLUDE) $(LIBFT_DIR)
	@ if [ $$? -eq 0 ]; then \
		echo "\033[32mNORMINETTE OK\033[0m"; \
	fi

-include	$(DEPS)