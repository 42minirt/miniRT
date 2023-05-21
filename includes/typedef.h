/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:43:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "minirt.h"

/********** typedef union **********/
typedef union u_shape_data			t_shape_data;

/********** typedef enum **********/
typedef enum e_shape_type			t_shape_type;
typedef enum e_parse_result			t_parse_res;
typedef enum e_identifier			t_identifier;
typedef enum e_light_type			t_light_type;

/********** typedef struct **********/
typedef struct s_all_info			t_all_info;
typedef struct s_mlx_info			t_mlx_info;
typedef struct s_scene_info			t_scene_info;
typedef struct s_camera_info		t_camera_info;
typedef struct s_color				t_color;
typedef struct s_img				t_img;
typedef struct s_light				t_light;
typedef struct s_obj				t_obj;
typedef struct s_vec				t_vec;
typedef struct s_obj_color			t_obj_color;
typedef struct s_ray				t_ray;
typedef struct s_intersection_point	t_intersection_point;
typedef struct s_plane_shape		t_plane;
typedef struct s_ball_shape			t_ball;
typedef struct s_sphere_shape		t_sphere;
typedef struct s_cylinder_shape		t_cylinder;
typedef struct s_corn_shape			t_corn;
typedef struct s_discriminant_param	t_d_param;
typedef struct s_intp_param_of_corn	t_corn_param;
typedef struct s_corn_ints			t_corn_ints;

////////////////////////////////////////////////////////
typedef union u_shape_data				t_shape_data;

/********** typedef enum **********/
//typedef enum e_shape_type				t_shape_type;
typedef enum e_parse_result				t_parse_res;
//typedef enum e_identifier				t_id;
//typedef enum e_light_type				t_light_type;

/********** typedef struct **********/
typedef struct s_all_info				t_all_info;
typedef struct s_mlx_info				t_mlx_info;
typedef struct s_scene_info				t_scene_info;
typedef struct s_camera_info			t_camera_info;
typedef struct s_color					t_color;
typedef struct s_img					t_img;
typedef struct s_light					t_light;
typedef struct s_obj					t_obj;
typedef struct s_vec					t_vec;
typedef struct s_obj_color				t_obj_color;
typedef struct s_ray					t_ray;
typedef struct s_intersection_point		t_intersection_point;
typedef struct s_plane_shape			t_plane;
typedef struct s_sphere_shape			t_sphere;
typedef struct s_cylinder_shape			t_cylinder;
typedef struct s_corn_shape				t_corn;
typedef struct s_discriminant_param		t_d_param;
typedef struct s_ints_param_of_corn		t_corn_param;
typedef struct s_corn_ints				t_corn_ints;
typedef struct s_calc_diffuse_ref_param	t_diffuse_param;
typedef struct s_matrix					t_matrix;
typedef struct s_basis_vec_world		t_basis_world;
typedef struct s_basis_vec_local		t_basis_local;
typedef struct s_texture_map			t_tangetnt_map;
typedef struct s_map_idx				t_map_idx;
typedef struct s_id_cnt					t_id_cnt;


///////////////////////////////////////////////////////////////////////////////

/********** enum **********/

//enum	e_identifier
//{
//	id_camera = 0,
//	id_ambient = 1,
//	id_point_light = 2,
//	id_spot_light = 3,
//	id_sphere = 4,
//	id_plane = 5,
//	id_cylinder = 6,
//	id_corn = 7,
//	id_invalid,
//};

enum	e_parse_result
{
	PASS = 10,
	ERROR_FATAL = 11,
	ERROR_INVALID_TYPE = 12,
	ERROR_LACK_INFO = 13,
	ERROR_TOO_MANY_INFO = 14,
	ERROR_INVALID_ARG = 15,
	ERROR_OUT_OF_RANGE = 16,
	ERROR_MULTIPLE_ID = 17,
	ERROR_MISSING_ID = 18,
	ERROR_INVALID_PPM_FORMAT = 19,
};

enum	e_shape_type
{
	BALL = 20,
	PLANE = 21,
	CORN = 22,
	CYLINDER = 23,
};

enum	e_light_type
{
	LT_POINT = 30,
	LT_SPOT = 31,
};

/////////////////////////////////////////////////
//enum	e_shape_type
//{
//	BALL = 20,
//	PLANE = 21,
//	CORN = 22,
//	CYLINDER = 23,
//};
//
//enum	e_light_type
//{
//	LT_POINT = 30,
//	LT_SPOT = 31,
//};

//////////////////////////////////////////////////

/********** struct & union **********/

// create unit
struct s_vec {
	double	x;
	double	y;
	double	z;
};

struct s_color
{
	double	r;
	double	g;
	double	b;
};

//---------------------------------------------

struct s_light
{
	const char		*id_type;

//	t_light_type	type;
	t_vec			point;
	t_vec			direction;
	double			brightness;
	t_color			light_color;// bonus
	double			sl_angle;// bonus
	double			sl_angle_half;// bonus
	t_vec			sl_dir;// bonus
};

//---------------------------------------------

struct s_sphere_shape
{
	t_vec	center;
	double	radius;
	double	diameter;
};

struct s_plane_shape
{
	t_vec	center;
	t_vec	normal;
};

struct s_cylinder_shape
{
	t_vec	bottom_center;
	t_vec	axis;
	double	radius;
	double	diameter;
	double	height;
};

struct s_corn_shape
{
	t_vec	bottom_center;
	t_vec	origin;
	t_vec	axis;
	double	radius;
	double	diameter;
	double	height;
};

union u_shape_data // sphere or plane
{
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_corn		corn;
};

//---------------------------------------------

// img.data=[R11,G11,B11, R12,G12,B12, ..., R21,G21,B21,..., Rhw,Ghw,Bhw]
struct	s_img
{
	size_t	height;
	size_t	width;
	int		*data;
};

// init: init_obj() in get_config_of_objects.c
struct s_obj_color
{
	t_color	ka;
	t_color	kd;
	t_color	ks;
	double	shininess;
	double	ia;
	double	id;
	double	is;
	bool	is_perfect_ref;
	t_color	kf;
	bool	is_checker;
	t_color	checker_color;
	bool	is_texture;
	t_img	texture_data;
	bool	is_bump;
	t_img	bump_data;
};

// ambient ref	// fix(0.1, 0.1, 0.1)
// diffuse ref	// rf_file
// specular ref	// fix (1.0, 1.0, 1.0)
// alpha, fix
// alpha, fix
// ia
// id
// is
// todo: ia, id, is は light依存？
//is_perfect_ref;	// init:false
// kf kf 完全鏡面反射光/屈折光係数RGB(1,1,1)で初期化
// is_checker;		// init:false



struct s_obj
{
	const char		*id_str;
	t_shape_data	shape_data;
	t_obj_color		obj_color;
};
//	t_shape_type	type; //shere or ... 不要？

//---------------------------------------------

// eye2screen
struct s_ray
{
	t_vec	pos;
	t_vec	unit_dir;
};

//---------------------------------------------

struct s_mlx_info
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_scene_info
{
	t_color	ambient_color;
	double	brightness;
	t_list	*lights;
	t_list	*objs;
};

// t_list	*lights; //content: light;
// t_list	*objs; //content : obj;

struct s_camera_info
{
	t_vec	position;
	t_vec	direction;
	double	fov_deg;
	t_ray	camera;
};

// t_vec	position;
// t_vec	direction;
// double	fov_deg;	//init:-1
// t_ray	camera;	//vec or matrix

struct s_all_info
{
	t_mlx_info		*mlx_info;
	t_scene_info	*scene_info;
	t_camera_info	*camera_info;
};

//---------------------------------------------

struct s_intersection_point
{
	double	distance;
	t_vec	position;
	t_vec	normal;
	t_obj	*obj;
};

// double	distance;	// 交点から目までの距離　tの値　元となるベクトルが単位ベクトルがtはサイズと重なる
// 	t_vec	position;	// 交点の位置ベクトル
// 	t_vec	normal;		// 交点における物体表面の法線ベクトル
// 	t_obj	*obj;

struct s_discriminant_param
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	double	t2;
};

struct s_ints_param_of_corn
{
	t_vec	vec_origin2pe;
	t_vec	vec_cross_de_n;
	t_vec	vec_cross_origin2pe_n;
	t_vec	vec_two_x_cross_de_n;
	t_vec	vec_n;
	double	ratio_r_h;
	double	half_of_vertex_angle;
	double	dot_de_n;
	double	dot_origin2pe_n;
	double	vec_norm_de_x_n;
	double	norm_cross_origin2pe_x_n;
};

// <<<<<<< HEAD
// 	t_vec	pe_po;
// 	t_vec	cross_de_n;
// 	t_vec	cross_pepo_n;
// 	t_vec	two_x_cross_de_n;
// 	t_vec	inv_axis;
// =======　不明

struct s_corn_ints
{
	t_vec	vec_pos;
	t_vec	vec_origin2pos;
	t_vec	vec_norm_origin2pos;
	t_vec	vec_normal;
	double	h;
};

// <<<<<<< HEAD
// 	t_vec	ti_d;
// 	t_vec	pos;
// 	t_vec	pos_po;
// 	t_vec	norm_pos_po;
// 	t_vec	normal;
// 	double	h;
// =======　不明

struct s_calc_diffuse_ref_param
{
	t_vec					vec_normal;
	t_vec					vec_pos2light;
	t_vec					vec_light2pos;
	double					dot_n_pos2light;
	t_ray					ray;
	t_intersection_point	its_p;
	t_light					*light;
};

struct	s_texture_map
{
	double	u;
	double	v;
};

struct s_map_idx
{
	size_t	row;
	size_t	col;
	size_t	idx;
};

struct s_id_cnt
{
	int	camera_cnt;
	int	ambient_cnt;
	int	point_light_cnt;
	int	spot_light_cnt;
	int	sphere_cnt;
	int	plane_cnt;
	int	cylinder_cnt;
	int	corn_cnt;
};

#endif //TYPEDEF_H