#ifndef DEBUG_H
# define DEBUG_H

# include "minirt.h"

void		debug_print_config(t_all_info *info);
const char	*parse_result_char(t_parse_res res);
void		print_sphere(t_obj *obj);
void		print_plane(t_obj *obj);
void		print_cylinder(t_obj *obj);
void		print_corn(t_obj *obj);

#endif //DEBUG_H
