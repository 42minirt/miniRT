/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:19:09 by user              #+#    #+#             */
/*   Updated: 2023/05/17 23:30:32 by user             ###   ########.fr       */
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
# define WINDOW_WIDTH	960
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

//単位ベクトル以外の情報に下記のように記載するのかどうか
//1 unit_vec
//2 size
//3 vec


/* nanika */
t_color		backgroundcolor_init();
void		colort_init_pointer(t_color *color);
t_color		calc_color(t_scene_info *scene_info, t_ray eye2screen);
void		color_add_pointer(t_color *tgt, t_color *t1, t_color *t2);
t_color		raytrace(t_all_info *info, t_ray eye2screen_xy);


/* destructor */
void	destruct_info(t_all_info *info);

/* mlx helper */
void	put_pixel(t_mlx_info *mlx_info, size_t x, size_t y, t_color color);


#endif