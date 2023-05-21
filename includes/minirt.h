/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:19:09 by user              #+#    #+#             */
/*   Updated: 2023/05/21 21:31:42 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/errno.h>
# include <math.h>

# include "../minilibx-linux/mlx.h"
# include "../libs/include/libft.h"

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
# define WINDOW_HEIGHT		540
# define WINDOW_WIDTH		960
# define WINDOW_TITLE		"miniRT"

/********** string **********/
# define OP_CHECKER_TEXTURE	"checker"
# define OP_PERFECT_REF		"perfect_ref"
# define OP_IMAGE_TEXTURE	"image"

/********** value **********/
# define MAX_RECURSION		8

/********** epsiron **********/
# define EPSIRON 			0.002

# define MT_PERFECT_REFLECTION 666

/********** key hook **********/
# define EVENT_DESTROY		33
# define EVENT_KEY_PRESS	2
# define KEY_ESC			0xff1b

/********** value **********/
# define MAX_RECURSION	8
# define IMG_FREQUENCY	1
# define PPM_RGB_UNIT	3
# define CHECKER_U_MAG	10
# define CHECKER_V_MAG	10
# define PARSING_YET	(-1.0)
//#define EPSILON		(1.0 / 512.0)
# define EPSILON		0.004
# define TO_RADIANS		(2.0 * M_PI / 180.0)
# define TO_DEGREES		(1.0 / TO_RADIANS)

/********** rt_id **********/
# define ID_AMBIENT		"A"
# define ID_CAMERA		"C"
# define ID_LIGHT		"L"
# define ID_SPOTLIGHT	"sl"
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

//単位ベクトル以外の情報に下記のように記載するのかどうか
//1 unit_vec
//2 size
//3 vec
/* nanika */

t_color			backgroundcolor_init(void);
void			colort_init_pointer(t_color *color);
t_color			calc_color(t_scene_info *scene_info, t_ray eye2screen);
void			color_add_pointer(t_color *tgt, t_color *t1, t_color *t2);
// t_color			raytrace(t_all_info *info, t_ray eye2screen_xy);

/* intersection */

// double			calc_planeratio(t_obj *obj,
// t_all_info *info, t_ray *ray, t_intersection_point *itsp);
// double			calc_cylinderratio(t_obj
// *obj, t_all_info *info, t_ray *eye2scr, t_intersection_point *tmp_itsp);
double			set_itsp(t_plane *plane, \
double t, t_ray *ray, t_intersection_point *itsp);

double			calc_intersect_with_sphere(t_obj *obj, t_ray ray, \
								t_intersection_point *intp);
double			calc_intersect_with_corn(t_obj *obj, t_ray ray, \
								t_intersection_point *intp);
void			solve_quadratic_equation(t_d_param *d_param);
double			get_valid_distance(double t1, double t2);
double			calc_discriminant(double a, double b, double c);
t_corn_param	calc_inpt_param_of_corn(t_corn *c, t_ray ray);
t_d_param		calc_d_param_of_corn(t_corn_param p);

/* destructor */

void			destruct_info(t_all_info *info);
void			free_objs(void *content);
void			free_lights(void *content);
void			x_free_1d_alloc(void **alloc);
void			x_free_2d_alloc(void ***alloc);

/* mlx helper */

void			put_pixel(t_mlx_info \
*mlx_info, size_t x, size_t y, t_color color);
void			mlx_hooks(t_mlx_info *mlx_info);

// t_color			calc_diffuse_reflection(t_all_info info,
// t_intersection_point its_p, t_ray eye2screen);
// t_color			calc_specular_reflection(t_all_info info,
// t_intersection_point its_p, t_ray eye2screen);
// t_color			calc_perfect_reflection(t_all_info info,
// t_intersection_point its_p, t_ray eye2screen);

#endif