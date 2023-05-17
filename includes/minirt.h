#ifndef MINIRT_H
# define MINIRT_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef	struct	s_list t_list;
typedef struct s_all_info t_all_info;
typedef struct s_color t_color;
typedef struct s_img t_img;
typedef	struct s_light t_light;
typedef struct	s_obj t_obj;
typedef enum e_type t_type;

struct s_color
{
	double	R;
	double	G;
	double	B;
};

struct s_list
{
	void	*content;
	t_list	*next;
};

struct s_light 
{ //t_list's content
    t_vec		point;
    double		brightness;
    t_color		light;
};

enum e_type
{
	BALL,
	PLANE,
	CORN,
	CYLINDER
};

struct s_obj 
{ // t_list's content
	// type
	t_type		type; //shere or ...

	// shape
	union		shape_data;

	// material
	t_obj_color	obj_color;
};

typedef struct	s_plane_shape
{
    t_vec	center;
    t_vec	normal;
}t_plane;

typedef struct	sphere_shape
{
    t_vec	center;
    double	radis;
}t_sphere;


typedef struct	cylinder_shape
{
    t_vec	bottom_center;
    t_vec	axis;

    double  radius;
    double  height;
}t_cylinder;

typedef struct	corn_shape
{
    t_vec	bottom_center;
    t_vec	axis;

    double  radius;
    double  height;
}t_corn;

typedef union	u_shape_data // sphere or plane
{
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_corn			corn;

} t_shape_data;

typedef struct s_obj_color
{
    t_color ka;
    t_color kd;
    t_color ks;
   

    Ia, Id, Is;

// bonus
    bool		is_perfect_ref;
    t_color		reflect_ref; // kf 完全鏡面反射光/屈折光係数RGB(1,1,1)で初期化
    
    bool is_checker;
	t_color   checker_color;
    
    bool    is_img;
	t_img   texture;
	t_img	bump;
}t_obj_color;

// intersect info ??



//////////////////////////////////////////////////////////////////////////////////////////

# define WINDOW_HEIGHT		540
# define WINDOW_WIDTH		960

typedef struct s_mlx_info t_mlx_info;
typedef struct s_scene_info t_scene_info;
typedef struct s_camera_info t_camera_info;

struct s_all_info {
	t_mlx_info		*mlx_info;
	t_scene_info	*scene_info;
	t_camera_info	*camera_info;
};

struct s_mlx_info{
	void		*mlx;
	void		*mlx_win;
	char		*addr;
};

struct s_scene_info {
	// ambient
	t_color	ambient;
	// lights
	t_list *lights; //content: light;
	// objs
	t_list *objs;   //content : obj;
};

// eye2screen
typedef struct s_ray {
	t_vec pos;
	t_vec unit_dir;
} t_ray;

struct s_camera_info {
	t_ray	camera;		//しばらく固定
	double 	fov;	//tmp -1 で初期化
	float	distance_camera_to_screen;

	// vec or matrix
};

typedef struct	s_intersection_point
{
	double	distance;	// 交点から目までの距離　tの値　元となるベクトルが単位ベクトルがtはサイズと重なる
	t_vec	position;	// 交点の位置ベクトル
	t_vec	normal;		// 交点における物体表面の法線ベクトル
	t_list	*obj;
} t_intersection_point;


//////////////////////// util

// create unit
typedef struct s_vec {
    double  x;
    double  y;
    double  z;
} t_vec;

struct s_color
{
    double r;
    double g;
    double b;
};

struct    s_img
{
    int    height;
    int		width;
    int    *data;    // data=[R11,G11,B11, R12,G12,B12, ..., R21,G21,B21,..., Rhw,Ghw,Bhw]
};

//単位ベクトル以外の情報に下記のように記載するのかどうか
//1 unit_vec
//2 size
//3 vec

//eyevecはどこにおくべきか

//mainで呼び出す関数を呼び出す

//ここまで

//eyevecの計算を行う関数　平面からワールドへ
t_ray get_screen_vector(t_all_info info);
//ここまで平面からワールド

//raytranceで行う関数を各箇所
t_color		raytrace(t_all_info info, t_ray eye2screen_xy);
//ここまでraytranceを行う

// calcvector ~~ベクトル計算をまとめる~~
void	    add_vec(t_vec *sub, t_vec *v1, t_vec *v2);
void		neg_vec(t_vec *sub, t_vec *v1, t_vec *v2);
double		dot_vec(t_vec *v1, t_vec *v2);
void		calc_outerproduct(t_vec *tgt_vec, t_vec *v1, t_vec *v2);
void    	t_mix_vec_all(t_vec *tgt_vec, double t1, t_vec *v1, double t2, t_vec *v2);
//ここまでベクトル計算//

// calcvector ~~ベクトルを正規化したりセットしたりする~~
void		setvec(t_vec *tgt_vec, double x, double y, double z);
void		normalize(t_vec *normal_vec, t_vec *normarized_vec);
void		inverse_vec(t_vec *inv_vec, t_vec *inved_vec);
double		obtain_vecsize(t_vec *vec);
void		times_vec(t_vec *tgt_vec, double t, t_vec *sub);
//ここまでベクトル正規化//

//colorに関する関数
void		color_set(t_color *tgt, double R, double G, double B);
void		color_add(t_color *tgt, t_color *t1, t_color *t2);

t_color		backgroundcolor_init();
t_color		calc_color(t_scene_info *scene_info, t_ray eye2screen);
t_all_info	construct_info();
bool		check_intersection(t_all_info info, t_ray eye2screen, t_intersection_point *its_p);

#endif