#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "minirt.h"

/********** typedef union **********/
typedef union	u_shape_data			t_shape_data;

/********** typedef enum **********/
typedef enum	e_shape_type			t_shape_type;
typedef enum	e_parse_result			t_parse_res;
typedef enum	e_identifier			t_identifier;
typedef enum	e_light_type			t_light_type;

/********** typedef struct **********/
typedef struct	s_all_info				t_all_info;
typedef struct	s_mlx_info				t_mlx_info;
typedef struct	s_scene_info			t_scene_info;
typedef struct	s_camera_info			t_camera_info;
typedef struct	s_color					t_color;
typedef struct	s_img					t_img;
typedef	struct	s_light					t_light;
typedef struct	s_obj					t_obj;
typedef struct	s_vec					t_vec;
typedef struct	s_obj_color				t_obj_color;
typedef struct	s_ray					t_ray;
typedef struct	s_intersection_point	t_intersection_point;
typedef struct	s_plane_shape			t_plane;
typedef struct	s_sphere_shape			t_sphere;
typedef struct	s_cylinder_shape		t_cylinder;
typedef struct	s_corn_shape			t_corn;
typedef struct	s_discriminant_param	t_d_param;
typedef struct	s_intp_param_of_corn	t_corn_param;
typedef struct	s_corn_ints				t_corn_ints;

//////////////////////////////////////////////////////////////////////////////////////////

/********** enum **********/

enum	e_identifier
{
	id_camera = 0,
	id_ambient = 1,
	id_point_light = 2,
	id_spot_light = 3,
	id_sphere = 4,
	id_plane = 5,
	id_cylinder = 6,
	id_corn = 7,
};

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

/********** struct **********/

// create unit
struct s_vec {
	double  x;
	double  y;
	double  z;
};

struct s_color
{
	double r;
	double g;
	double b;
};

//---------------------------------------------

struct s_light
{
	t_light_type	type;
	t_vec			point;
	double			brightness;

	// bonus
	t_color			light_color;
	double			sl_angle;
};

//---------------------------------------------

struct	s_plane_shape
{
	t_vec	center;
	t_vec	normal;
};

struct	s_sphere_shape
{
	t_vec	center;
	double	radius;
	double	diameter;
};

struct	s_cylinder_shape
{
	t_vec	bottom_center;
	t_vec	axis;

	double  radius;
	double	diameter;
	double  height;
};

struct	s_corn_shape
{
	t_vec	bottom_center;
	t_vec	axis;
	t_vec	origin;

	double  radius;
	double	diameter;
	double  height;
};

/********** union **********/
union	u_shape_data // sphere or plane
{
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_corn		corn;
};

struct    s_img
{
	int	height;
	int	width;
	int	*data;    // data=[R11,G11,B11, R12,G12,B12, ..., R21,G21,B21,..., Rhw,Ghw,Bhw]
};

struct s_obj_color
{
	t_color ka; // ambient ref
	t_color kd; // diffuse ref
	t_color ks; // specular ref //fix

	double	shininess;	// alpha

	double	ia;
	double	id;
	double	is;

// bonus
	bool	is_perfect_ref;
	t_color	perfect_ref_color; // kf 完全鏡面反射光/屈折光係数RGB(1,1,1)で初期化

	bool 	is_checker;
	t_color	checker_color;

	t_img	texture_data;
	t_img	bump_data;
};

struct s_obj
{ // t_list's content
	// type
	t_shape_type	type; //shere or ...

	// shape
	t_shape_data	shape_data;

	// material
	t_obj_color		obj_color;
};

//---------------------------------------------

struct s_all_info {
	t_mlx_info		*mlx_info;
	t_scene_info	*scene_info;
	t_camera_info	*camera_info;
};

struct s_mlx_info{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;

	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_scene_info {
	t_color	ambient_color;
	double	brightness;
	t_list *lights;		 //content: light;
	t_list *objs;		//content : obj;
};

// eye2screen
struct s_ray {
	t_vec pos;
	t_vec unit_dir;
};

struct s_camera_info {
	t_ray	camera;		//しばらく固定
	double 	fov;	//tmp -1 で初期化
	float	distance_camera_to_screen;
	// vec or matrix
};

struct	s_intersection_point
{
	double	distance;	// 交点から目までの距離　tの値　元となるベクトルが単位ベクトルがtはサイズと重なる
	t_vec	position;	// 交点の位置ベクトル
	t_vec	normal;		// 交点における物体表面の法線ベクトル
	t_list	*obj;
};

struct	s_discriminant_param
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	double	t2;
};

struct	s_intp_param_of_corn
{
	t_vec	pe_po;
	t_vec	cross_de_n;
	t_vec	cross_pepo_n;
	t_vec	two_x_cross_de_n;

	t_vec	inv_axis;

	double	ratio_r_h;
	double	half_of_vertex_angle;

	double	dot_de_n;
	double	dot_pepo_n;
	double	norm_de_x_n;
	double	norm_pepo_x_n;
};

struct	s_corn_ints
{
	t_vec	ti_d;
	t_vec	pos;
	t_vec	pos_po;
	t_vec	norm_pos_po;

	t_vec	normal;

	double	h;
};

#endif //TYPEDEF_H
