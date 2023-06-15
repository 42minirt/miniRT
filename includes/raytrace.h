/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:39:36 by takira            #+#    #+#             */
/*   Updated: 2023/06/12 18:05:03 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "typedef.h"

/* intersection */
bool			check_intersection(t_scene_info *scene, \
									t_ray eye2screen, \
									t_intersection_point *its_p);

t_ray			red_rayvec(t_camera_info *camera_info, double x, double y);

double			calc_planeratio(t_obj *obj, \
								t_ray *ray, \
								t_intersection_point *itsp);
double			calc_cylinderratio(t_obj *obj, \
									t_ray *eye2scr, \
									t_intersection_point *tmp_itsp);
double			calc_intersect_with_sphere(t_obj *obj, t_ray ray, \
											t_intersection_point *intp);
double			calc_intersect_with_corn(t_obj *obj, \
											t_ray ray, \
											t_intersection_point *intp);
void			solve_quadratic_equation(t_d_param *d_param);
double			get_valid_distance(double t1, double t2);
double			calc_discriminant(double a, double b, double c);
t_corn_param	calc_ints_param_of_corn(t_corn *c, t_ray ray);
t_d_param		calc_d_param_of_corn(t_corn_param p);
t_corn_ints		calc_ints(t_corn *corn, \
							t_ray ray, \
							t_corn_param p, \
							double t);

/* raytracing */
t_color			raytrace(t_all_info *info, t_ray eye2screen);
t_color			recursive_raytrace(t_all_info *info, \
									t_ray eye2screen, \
									size_t counter);
t_color			calc_ambient_reflection(t_scene_info *scene, \
										t_intersection_point its_p);
t_color			calc_diffuse_reflection(t_scene_info *scene, \
										t_intersection_point its_p, \
										t_ray eye2screen);
t_color			calc_specular_reflection(t_all_info *info, \
										t_intersection_point *its_p, \
										t_ray eye2screen);
t_color			calc_perfect_reflection(t_all_info *info, \
										t_intersection_point *its_p, \
										t_ray eye2screen, \
										size_t counter);
t_vec			get_bump_normal(t_intersection_point *its_p);
t_vec			get_normal(t_intersection_point *its_p);

t_vec			get_pl_sp_drawable_normal(t_intersection_point itsp, \
											t_vec ray_dir);
double			calc_dot_n_l(t_intersection_point itsp, \
								t_ray ray, \
								t_vec unit_pos2light);

/* calc_diffuse_color */
t_color			get_itspos_image_texture_color(t_intersection_point its_p);
t_color			get_itspos_checker_color(t_intersection_point its_p);
t_diffuse_param	calc_diffuse_param(t_intersection_point *its_p, \
									t_ray *ray, \
									t_light *light);
bool			is_in_range_spotlight(t_vec unit_light2pos, t_light *light);
/* is_condition */
bool			is_obj_bump_texture(t_obj_color obj_color);
bool			is_obj_image_texture(t_obj_color obj_color);
bool			is_obj_perfect_ref(t_obj_color obj_color);
bool			is_obj_checker(t_obj_color obj_color);
bool			is_obj_btw_pos_light(t_scene_info *scene, \
														t_vec pos, \
														t_vec pos2light);

/* get_its_pos_img_color */
t_tangetnt_map	get_tangent_coordinate_map(t_intersection_point *its_p);

//一旦ここに置いとく
double			check_intersection_t1(t_vec *d_n, \
										t_vec *ac_n, \
										t_cylinder *cyl, t_ray *ray);
void			set_intersection_t1(t_intersection_point *itp, \
										double t, \
										t_cylinder *cyl, \
										t_ray *ray);
double			check_intersection_t2(t_vec *d_n, \
										t_vec *ac_n, \
										t_cylinder *cyl, \
										t_ray *ray);
void			set_intersection_t2(t_intersection_point *itp, \
									double t, \
									t_cylinder *cyl, \
									t_ray *ray);

/* is_camera_and_light_overlap_with_obj */
bool			is_camera_and_light_overlap_with_obj(t_all_info *info);
bool			ch_conflict_corn(t_corn obj, t_vec pos);
bool			ch_conflict_cylinder(t_cylinder obj, t_vec pos);
bool			ch_conflict_plane(t_plane obj, t_vec pos);
bool			ch_conflict_sphere(t_sphere obj, t_vec pos);

#endif //RAYTRACE_H
