#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <sys/errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <math.h>

# include "./../minilibx-linux/mlx.h"
# include "./../libs/include/libft.h"

# define OPEN_ERROR		(-1)
# define CLOSE_ERROR	(-1)

# define WINDOW_HEIGHT	540
# define WINDOW_WIDTH	960
# define WINDOW_TITLE	"miniRT"

#define OP_CHECKER_TEXTURE	"checker"
#define OP_PERFECT_REF		"perfect_ref"
#define OP_IMAGE_TEXTURE	"image"

#define MAX_RECURSION	8

/* typedef */
typedef struct	s_all_info		t_all_info;
typedef struct	s_mlx_info		t_mlx_info;
typedef struct	s_scene_info	t_scene_info;
typedef struct	s_camera_info	t_camera_info;
typedef struct	s_color			t_color;
typedef struct	s_img			t_img;
typedef	struct	s_light			t_light;
typedef struct	s_obj			t_obj;
typedef struct	s_vec			t_vec;
typedef struct	s_obj_color		t_obj_color;
typedef struct	s_ray			t_ray;

typedef struct	s_intersection_point	t_intersection_point;

typedef struct	s_plane_shape		t_plane;
typedef struct	s_sphere_shape		t_sphere;
typedef struct	s_cylinder_shape	t_cylinder;
typedef struct	s_corn_shape		t_corn;

typedef union	u_shape_data		t_shape_data;

typedef enum	e_type				t_type;
typedef enum	e_parse_result		t_parse_res;
typedef enum	e_identifier		t_identifier;
typedef enum	e_light_type		 t_light_type;

/* enum */

enum	e_type
{
	BALL,
	PLANE,
	CORN,
	CYLINDER
};

enum	e_parse_result
{
	PASS,

	ERROR_FATAL,
	ERROR_INVALID_TYPE,
	ERROR_LACK_INFO,

	ERROR_TOO_MANY_INFO,
	ERROR_INVALID_ARG,
	ERROR_OUT_OF_RANGE,
	ERROR_MULTIPLE_ID,
};

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

enum	e_light_type
{
	LT_POINT,
	LT_SPOT,
};

//////////////////////////////////////////////////////////////////////////////////////////

union	u_shape_data // sphere or plane
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_corn		*corn;

};

//////////////////////////////////////////////////////////////////////////////////////////

/* struct */

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

//////////////////////////////////////////////////////////////////////////////////////////

struct s_light
{
	t_light_type	type;
    t_vec			point;
    double			brightness;

	// bonus
    t_color			light_color;
	double			sl_angle;	//todo:init
};

//////////////////////////////////////////////////////////////////////////////////////////


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

    double  radius;
	double	diameter;
    double  height;
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
    
	t_img	*texture_data;
	t_img	*bump_data;
};


struct    s_img
{
	int	height;
	int	width;
	int	*data;    // data=[R11,G11,B11, R12,G12,B12, ..., R21,G21,B21,..., Rhw,Ghw,Bhw]
};

//////////////////////////////////////////////////////////////////////////////////////////


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
	// ambient
	t_color	ambient_color;
	double	brightness;
	// lights
	t_list *lights; //content: light;
	// objs
	t_list *objs;   //content : obj;
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


// constructor, destructor
int			construct_info(t_all_info *all_info, const char *rt_path);
int			parsing_config(t_all_info *all_info, const char *rt_path);

t_parse_res validate_scene(t_scene_info *scene_info);
t_parse_res validate_camera(t_camera_info *camera_info);

t_parse_res	get_ambient_setting(const char *line, t_scene_info *scene);
t_parse_res	get_lights_setting(const char *line, t_scene_info *scene, int id_no);
t_parse_res	get_objects_setting(const char *line, t_scene_info *scene, int id_no);
t_parse_res	get_camera_setting(const char *line, t_camera_info *camera);

// parsing helper
void		skip_spece(const char *line, size_t *idx);
void		skip_delimiter(const char *line, size_t *idx);
void		increment_idx_to_next_format(const char *line, size_t *idx, char *prev_str);
char		*get_identifier_str(const char *line, size_t idx);
int			get_identifier_no(const char *id_str);
double		ft_strtod(const char *str, bool *is_success, char **err);

// parsing digits
int			parsing_int_num(const char *line, int *int_num, size_t *idx);
int			parsing_double_num(const char *line, double *double_num, size_t *idx);
int			parsing_vec(const char *line, t_vec *vec, size_t *idx);
int			parsing_color(const char *line, t_color *color, size_t *idx);



void		update_scene(t_scene_info *scene);
void 		destruct_info(t_all_info info);


// vectoer
void    add_vec(t_vec *sub, t_vec *v1, t_vec *v2);
void	neg_vec(t_vec *sub, t_vec *v1, t_vec *v2);
void	calc_outerproduct(t_vec *tgt_vec, t_vec *v1, t_vec *v2);
void    t_mix_vec_all(t_vec *tgt_vec, double t1, t_vec *v1, double t2, t_vec *v2);
void	setvec(t_vec *tgt_vec, double x, double y, double z);
void	normalize(t_vec *normal_vec, t_vec *normarized_vec);
void	inverse_vec(t_vec *inv_vec, t_vec *inved_vec);



// color
t_color	color_mul_k1c1k2c2(const t_color *c, double k1, const t_color *c1, double k2, const t_color *c2);
t_color	color_k1c1k2c2(double k1, const t_color *c1, double k2, const t_color *c2);
t_color	color_k1c1(double k1, const t_color c1);
t_color	color_add(const t_color c1, const t_color c2);
t_color	init_color(double r, double g, double b);

// get_obj_detail
t_parse_res	get_obj_detail(const char *line, int id_no, t_obj *obj);
t_parse_res	get_bonus_detail(const char *line, t_obj *obj, size_t *idx);
t_parse_res	get_image_texture(const char *line, t_img *obj_color, size_t *idx);

int			get_img(t_img *img, int fd);


// mlx_helpers
void	put_pixel(t_mlx_info *mlx_info, size_t x, size_t y, t_color color);


#endif