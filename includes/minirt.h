#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <stdio.h>
# include <math.h>

# define SUCCESS	0
# define FAILURE	1

typedef	struct	s_list			t_list;
typedef struct	s_all_info		t_all_info;
typedef struct	t_color			t_color;
typedef struct	s_img			t_img;
typedef	struct	s_light			t_light;
typedef struct	s_obj			t_obj;
typedef struct	s_vec			t_vec;
typedef struct	s_obj_color		t_obj_color;

typedef struct	s_plane_shape		t_plane;
typedef struct	s_sphere_shape		t_sphere;
typedef struct	s_cylinder_shape	t_cylinder;
typedef struct	s_corn_shape		t_corn;

typedef union	u_shape_data		t_shape_data;

typedef enum	e_type				t_type;


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

struct s_list
{
	void	*content;
	t_list	*next;
};

struct s_light 
{
    t_vec		point;
    double		brightness;
    t_color		*light;
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
	t_type			type; //shere or ...

	// shape
	t_shape_data	*shape_data;

	// material
	t_obj_color		*obj_color;
};


struct	s_plane_shape
{
    t_vec	center;
    t_vec	normal;
};

struct	sphere_shape
{
    t_vec	center;
    double	radis;
};


struct	cylinder_shape
{
    t_vec	bottom_center;
    t_vec	axis;

    double  radius;
    double  height;
};

struct	corn_shape
{
    t_vec	bottom_center;
    t_vec	axis;

    double  radius;
    double  height;
};

union	u_shape_data // sphere or plane
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*Icylinder;
	t_corn		*corn;

};

struct s_obj_color
{
    t_color *ka;
    t_color *kd;
    t_color *ks;
   
	double	ia;
	double	id;
	double	is;

// bonus
    bool	is_perfect_ref;
    t_color	*reflect_ref; // kf 完全鏡面反射光/屈折光係数RGB(1,1,1)で初期化
    
    bool 	is_checker;
	t_color	*checker_color;
    
    bool	is_img;
	t_img	*texture;
	t_img	*bump;
};



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
	t_color	*ambient;
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

/////////////////
t_color		backgroundcolor_init();
t_color		calc_color(t_scene_info *scene_info, t_ray eye2screen);
bool		check_intersection(t_all_info info, t_ray eye2screen, t_intersection_point *its_p);
t_color		raytrace(t_all_info info, t_ray eye2screen_xy);

int		construct_info(t_all_info *all_info);
void 	destruct_info(t_all_info info);


#endif