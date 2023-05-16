#ifndef CONSTRUCTOR_H
# define CONSTRUCTOR_H

# include "minirt.h"

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

// get_obj_detail
t_parse_res	get_obj_detail(const char *line, int id_no, t_obj *obj);
t_parse_res	get_bonus_detail(const char *line, t_obj *obj, size_t *idx);
t_parse_res	get_image_texture(const char *line, t_img *obj_color, size_t *idx, bool *empty);

t_parse_res	get_img(t_img *img, int fd);
#endif //CONSTRUCTOR_H
