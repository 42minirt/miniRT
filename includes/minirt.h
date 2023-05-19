/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:19:09 by user              #+#    #+#             */
/*   Updated: 2023/05/18 19:55:48 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/errno.h>
# include <math.h>

# include "./../minilibx-linux/mlx.h"
# include "./../libs/include/libft.h"

# include "typedef.h"

# include "color.h"
# include "constructor.h"
# include "debug.h"
# include "matrix.h"
# include "raytrace.h"
# include "vector.h"

/********** return value **********/
# define OPEN_ERROR		(-1)
# define CLOSE_ERROR	(-1)

/********** window **********/
# define WINDOW_HEIGHT	540
# define WINDOW_WIDTH	540
//# define WINDOW_WIDTH	960
# define WINDOW_TITLE	"miniRT"

/********** string **********/
#define OP_CHECKER_TEXTURE	"checker"
#define OP_PERFECT_REF		"perfect_ref"
#define OP_IMAGE_TEXTURE	"image"

/********** value **********/
#define MAX_RECURSION	8
#define IMG_FREQUENCY	1
#define	PPM_RGB_UNIT	3
#define CHECKER_U_MAG	10
#define CHECKER_V_MAG	10
#define	EPSILON			(1.0 / 512.0)
//#define	EPSILON			(1.0 / 256.0)

/********** key hook **********/
# define EVENT_DESTROY		33
# define EVENT_KEY_PRESS	2
# define KEY_ESC			0xff1b

#define MIN(a, b)	(a <= b ? a : b)
#define MAX(a, b)	(a >= b ? a : b)
#define CLAMP(val, minval, maxval)	MIN(MAX(val, minval), maxval)


//単位ベクトル以外の情報に下記のように記載するのかどうか
//1 unit_vec
//2 size
//3 vec

/* nanika */
t_color		backgroundcolor_init();


/* destructor */
void		destruct_info(t_all_info *info);

/* mlx helper */
void		my_mlx_pixel_put(t_mlx_info *mlx_info, size_t x, size_t y, int color);
void		put_pixel(t_mlx_info *mlx_info, size_t x, size_t y, t_color color);
void		mlx_hooks(t_mlx_info *mlx_info);

#endif