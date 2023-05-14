#ifndef MINIRT_H
# define MINIRT_H


struct scenes {
	// ambient

	// lights
	t_list *lights; content: light

	// objs
	t_list *objs;   content : obj

}

struct light { //t_list's content
    vec point;
    double  brightness;
    color   light_color;
}


struct obj { // t_list's content
	// type
	enum type //shere or ...

	// shape
	union shape_data

	// material
	obj_color
}

typedef union	u_shape_data // sphere or plane
{
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_corn			corn;

} t_shape_data;

plane_shape
{
    vec center;
    vec normal;
}

sphere_shape
{
    vec     center;
    double  radis;
}


cylinder_shape
{
    vec bottom_center;
    vec axis;

    double  radius;
    double  height;
}

corn_shape
{
    vec bottom_center;
    vec axis;

    double  radius;
    double  height;
}

obj_color
{
    t_color ka;
    t_color kd;
    t_color ks;
   

    Ia, Id, Is;

// bonus
    bool    is_perfect_ref
    color   reflect_ref = (1,1,1); // kf 完全鏡面反射光/屈折光係数RGB
    
    bool is_checker;
	color   checker_color;
    
    bool    is_img;
	t_img   texture;
	t_img	bump;
}

// intersect info ??



//////////////////////////////////////////////////////////////////////////////////////////

# define WINDOW_HEIGHT		540
# define WINDOW_WIDTH		960

struct info {
	// mlx parameter
    void		*mlx;
	void		*mlx_win;
	char		*addr;

	// scenes


	// camera
    //  vec or matrix later
}

// create unit
typedef struct s_vec {
    double  x;
    double  y;
    double  z;
} t_vec;

typedef struct s_color
{
    double r;
    double g;
    doubel b;
}   t_color;

//単位ベクトル以外の情報に下記のように記載するのかどうか
//1 unit_vec
//2 size
//3 vec

//eyevecはどこにおくべきか



#endif