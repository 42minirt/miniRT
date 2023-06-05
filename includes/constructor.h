/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:32:51 by user              #+#    #+#             */
/*   Updated: 2023/05/21 18:32:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTRUCTOR_H
# define CONSTRUCTOR_H

# include "minirt.h"

// constructor, destructor
int			construct_info(t_all_info *all_info, const char *rt_path);
t_parse_res	parsing_config(t_all_info *all_info, const char *rt_path);
t_parse_res	validate_scene(t_scene_info *scene_info);
t_parse_res	validate_camera(t_camera_info *camera_info);
t_parse_res	get_config_of_ambient(const char *line, t_scene_info *scene);
t_parse_res	get_config_of_lights(const char *line, \
								t_scene_info *scene, const char *id_str);
t_parse_res	get_config_of_objects(const char *line, \
								t_scene_info *scene, const char *id_str);
t_parse_res	get_congfig_of_camera(const char *line, t_camera_info *camera);

// parsing helper
void		skip_isspece(const char *line, size_t *idx);
void		skip_delimiter(const char *line, size_t *idx);
void		skip_delimiter_and_cnt_comma(const char *line, size_t *idx, size_t *cnt);

void		increment_idx_to_next_format(const char *line, \
											size_t *idx, char *prev_str);
char		*get_identifier_str(const char *line, size_t idx);
//t_id		get_identifier_no(const char *id_str);
double		ft_strtod(const char *str, bool *is_success, char **err);
long		ft_strtol(const char *str, bool *is_of, char **endptr);

// parsing digits
t_parse_res	parse_int(const char *line, size_t *idx, int *int_num);
t_parse_res	parse_double(const char *line, double *double_num, size_t *idx);
t_parse_res	parse_vec(const char *line, t_vec *vec, size_t *idx);
t_parse_res	parse_color(const char *line, t_color *color, size_t *idx);
void		update_scene_config(t_scene_info *scene);
void		update_camera_config(t_camera_info *camera);

// get_config_of_each_obj
t_parse_res	get_config_of_each_obj(const char *line, t_obj *obj);
t_parse_res	get_bonus_config_of_obj(const char *line, t_obj *obj, size_t *idx);
t_parse_res	get_image_texture(const char *line, \
								t_img *obj_color, size_t *idx, bool *empty);

// validate_is
bool		is_normal_vec_in_range(t_vec vec);
bool		is_vec_in_range(t_vec vec);
bool		is_color_in_range(t_color color);
bool		is_ratio_in_range(double ratio);
bool		is_angle_in_range(double angle_degree);
bool		is_fov_in_range(double fov_degree);
bool		is_comment_line(char c);
bool		is_num_in_valid_range(double num);

t_parse_res	validate_obj_shape(t_obj *obj);
t_parse_res	validate_obj_color(t_obj *obj);
t_parse_res	validate_lights_info(t_scene_info *scene);
t_parse_res	validate_ambient_info(t_scene_info *scene);

// update param
void		update_scene_sphere_info(t_sphere *sphere);
void		update_scene_plane_info(t_plane *plane);
void		update_scene_cylinder_info(t_cylinder *cylinder);
void		update_scene_corn_info(t_corn *corn);
void		update_config_lights(t_scene_info *scene);

// id_cnt
t_id_cnt	init_id_cnt(void);
t_parse_res	validate_id_cnt(t_id_cnt cnt);
void		increment_id_cnt(const char *id_str, t_id_cnt *cnt);
t_parse_res	validate_id(const char *id_str);

// validate file
int			validate_filename(const char *path, const char *extension);

// get_config
t_parse_res	get_config(const char *id_str, \
										const char *line, t_all_info *all);

t_parse_res	ret_res_and_free(t_parse_res ret, void **ptr);

// parsing ppm
t_parse_res	get_img_data(t_img *img, int fd);
t_parse_res	parse_ppm_data(t_img *img, int fd, t_ppm_param *p);
t_parse_res	put_ppmerr_ret_res(char *err);
t_parse_res	parse_ppm_data_line_by_line(const char *line, \
										t_ppm_param *p, t_img *img);
t_parse_res	init_data_array(t_img *img, t_ppm_param *p);

#endif //CONSTRUCTOR_H