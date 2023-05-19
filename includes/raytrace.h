/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:39:36 by takira            #+#    #+#             */
/*   Updated: 2023/05/18 19:55:36 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "minirt.h"

/* intersection */
bool	check_intersection(t_scene_info *scene, t_ray eye2screen, t_intersection_point *its_p);

double			calc_planeratio(t_obj *obj, t_ray *ray, t_intersection_point *itsp);
double			calc_cylinderratio(t_obj *obj, t_ray *eye2scr, t_intersection_point *tmp_itsp);
double			set_itsp(t_plane *plane, double t, \
							t_ray *ray, t_intersection_point *itsp);
double			calc_intersect_with_sphere(t_obj *obj, t_ray ray, \
											t_intersection_point *intp);
double			calc_intersect_with_corn(t_obj *obj, t_ray ray, \
											t_intersection_point *intp);
void			solve_quadratic_equation(t_d_param *d_param);
double			get_valid_distance(double t1, double t2);
double			calc_discriminant(double a, double b, double c);
t_corn_param	calc_ints_param_of_corn(t_corn *c, t_ray ray);
t_d_param		calc_d_param_of_corn(t_corn_param p);

/* raytracing */
bool			raytrace(t_all_info *info, t_ray eye2screen, t_color *color);
t_color			calc_ambient_reflection(t_scene_info *scene, t_intersection_point its_p);
t_color			calc_diffuse_reflection(t_scene_info *scene, \
									t_intersection_point its_p, t_ray eye2screen);
t_color			calc_specular_reflection(t_all_info *info, \
							t_intersection_point *its_p, t_ray eye2screen);
t_color			calc_perfect_reflection(t_all_info *info, \
							t_intersection_point *its_p, t_ray eye2screen);
t_vec			get_bump_normal(t_intersection_point *its_p);


/* calc_diffuse_color */
t_color			get_image_texture_ref_color(t_diffuse_param p);
t_diffuse_param	calc_diffuse_param(t_intersection_point *its_p, t_ray *ray, t_light *light);

/* is_condition */
bool			is_bump_data_exists(t_obj_color obj_color);
bool			is_image_data_exists(t_obj_color obj_color);
bool			is_obj_perfect_ref(t_obj_color obj_color);
bool			is_obj_checker(t_obj_color obj_color);
bool			is_obj_exists_between_itspos_and_light(t_scene_info *scene, t_diffuse_param p);

/* get_its_pos_img_color */
t_tangetnt_map	get_tangent_coordinate_map(t_intersection_point *its_p);

#endif //RAYTRACE_H
