#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "minirt.h"

/* intersection */
double			calc_planeratio(t_obj *obj, t_all_info *info, \
									t_ray *ray, t_intersection_point *itsp);
double			calc_cylinderratio(t_obj *obj, t_all_info *info, \
								t_ray *eye2scr, t_intersection_point *tmp_itsp);
double			set_itsp(t_plane *plane, double t, \
							t_ray *ray, t_intersection_point *itsp);

double			calc_intersect_with_sphere(t_obj *obj, t_ray ray, \
											t_intersection_point *intp);
double			calc_intersect_with_corn(t_obj *obj, t_ray ray, \
											t_intersection_point *intp);
void			solve_quadratic_equation(t_d_param *d_param);
double			get_valid_distance(double t1, double t2);
double			calc_discriminant(double a, double b, double c);
t_corn_param	calc_inpt_param_of_corn(t_corn *c, t_ray ray);
t_d_param		calc_d_param_of_corn(t_corn_param p);

/* raytracing */
bool	raytrace(t_all_info *info, t_ray eye2screen, t_color *color);

t_color	calc_ambient_reflection(t_scene_info *scene);
t_color	calc_diffuse_reflection(t_scene_info *scene, \
							t_intersection_point *its_p, t_ray eye2screen);
t_color	calc_specular_reflection(t_all_info *info, \
							t_intersection_point *its_p, t_ray eye2screen);
t_color	calc_perfect_reflection(t_all_info *info, \
							t_intersection_point *its_p, t_ray eye2screen);

#endif //RAYTRACE_H
