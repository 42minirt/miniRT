#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <sys/errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <math.h>

# include "./../minilibx-linux/mlx.h"
# include "./../libs/include/libft.h"

# include "typedef.h"
# include "vector.h"
# include "color.h"
# include "constructor.h"
# include "debug.h"

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

//単位ベクトル以外の情報に下記のように記載するのかどうか
//1 unit_vec
//2 size
//3 vec

//eyevecはどこにおくべきか

/*  */
t_color		backgroundcolor_init();
t_color		calc_color(t_scene_info *scene_info, t_ray eye2screen);
bool		check_intersection(t_all_info info, t_ray eye2screen, \
								t_intersection_point *its_p);
t_color		raytrace(t_all_info info, t_ray eye2screen_xy);


/* intersection */
bool	is_intersect_with_sphere(t_shape_data *shape, t_ray ray, \
								t_intersection_point *intp);


/* destructor */
void	destruct_info(t_all_info *info);

/* mlx helper */
void	put_pixel(t_mlx_info *mlx_info, size_t x, size_t y, t_color color);


#endif