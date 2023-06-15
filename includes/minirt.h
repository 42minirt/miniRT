/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:19:09 by user              #+#    #+#             */
/*   Updated: 2023/06/14 21:28:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/errno.h>
# include <unistd.h>

# include "../libs/include/libft.h"
# include "../libs/include/ft_gnl.h"
# include "../libs/include/ft_math.h"
# include "../libs/include/ft_printf.h"
# include "../libs/include/ft_put.h"
# include "../libs/include/ft_std.h"
# include "../libs/include/ft_string.h"

# include "typedef.h"
//# include "constructor.h"
//# include "debug.h"
//# include "matrix.h"
//# include "raytrace.h"
//# include "vector.h"
//# include "sys.h"

/********** return value **********/
# define OPEN_ERROR		(-1)
# define CLOSE_ERROR	(-1)

/********** window **********/
# define WINDOW_HEIGHT		540
//# define WINDOW_WIDTH		540
# define WINDOW_WIDTH		1080
# define WINDOW_TITLE		"miniRT"

/********** Ray Trace Setting Const **********/
// get_config_of_objects.c
# define SPECULAR_SHININESS		(10) // tmp
# define KA_COLOR				(0xBBBBBB)
# define KS_COLOR				(0x777777)
# define KS_COLOR_PLANE			(0x222222)
# define KF_COLOR				(0xFFFFFF)
# define RED_MASK				(0xFF0000)
# define GREEN_MASK				(0x00FF00)
# define BLUE_MASK				(0x0000FF)
# define INTENSITY_OF_AMBIENT	(0.1) // Ia TODO: 0.1の根拠
# define INTENSITY_OF_DIFFUSE	(0.7) // Id

/********** value **********/
# define FOV_DEG_MIN	(0.0)
# define FOV_DEG_MAX	(180.0)
# define ANGLE_DEG_MIN	(0.0)
# define ANGLE_DEG_MAX	(180.0)
# define RATIO_MIN		(0.0)
# define RATIO_MAX		(1.0)
# define NORMAL_MIN		(-1.0)
# define NORMAL_MAX		(1.0)
# define MAX_RECURSION	8
# define IMG_FREQUENCY	1
# define PPM_RGB_UNIT	3
# define CHECKER_U_FREQ	10
# define CHECKER_V_FREQ	10
# define BUMP_TO_NORMAL	(0.5)

/********** ppm **********/
# define PPM_X			3
# define COLOR_MIN		0
# define COLOR_MAX		255
# define COMMENT_FLAG	'#'

/********** string **********/
# define OP_CHECKER_TEXTURE	"checker"
# define OP_PERFECT_REF		"perfect_ref"
# define OP_IMAGE_TEXTURE	"image"

/********** value **********/
# define MAX_RECURSION		8
# define COLOR_DATA_KIND	3
# define PARSE_INIT			0

/********** epsiron **********/
# define EPSIRON 			(0.0000002)
# define EPSILON_DIVISOR	(65536.0)

/********** key hook **********/
# define EVENT_DESTROY		33
# define EVENT_KEY_PRESS	2
# define KEY_ESC			0xff1b

/********** rt_id **********/
# define ID_AMBIENT		"A"
# define ID_CAMERA		"C"
# define ID_LIGHT		"L"
# define ID_SPOTLIGHT	"SL"
# define ID_SPHERE		"sp"
# define ID_PLANE		"pl"
# define ID_CYLINDER	"cy"
# define ID_CORN		"co"

/********** rt_string **********/
# define OP_CHECKER_TEXTURE	"checker"
# define OP_PERFECT_REF		"perfect_ref"
# define OP_IMAGE_TEXTURE	"image"

/********** file extension **********/
# define RT_EXTENSION		".rt"
# define IMG_EXTENSION		".ppm"

/********** message **********/
# define MSG_ERROR				"Error\n"
# define MSG_MISSING_ARG		"rt_file required"
# define MSG_INVALID_RT			"rt_file invalid"
# define MSG_CAMERA_OVERLAP		"C overlap with Object"
# define MSG_LIGHT_OVERLAP		"L overlap with Object"
# define MSG_ERR_NOMEM			"Failure in memory allocate"
# define MSG_ERR_MLX			"Failure in init minilibx"
# define MSG_ERR_CONFIG			"Failure in parsing config file"
# define MSG_ERR_DIV_BY_ZERO	"division by zero in normalize."

typedef struct s_all_info	t_all_info;
typedef struct s_mlx_info	t_mlx_info;
typedef struct s_color		t_color;

/* main */
int				draw(t_all_info *info);

/* destructor */
void			destruct_info(t_all_info *info);
void			free_objs(void *content);
void			free_lights(void *content);

/* mlx helper */
void			put_pixel(t_mlx_info *mlx_info, \
							size_t x, \
							size_t y, \
							t_color color);
void			mlx_put_image(t_all_info info);
void			mlx_hooks(t_all_info *info);
double			clamp(double num, double min, double max);

#endif