#include "minirt.h"

t_color	get_checker_ref_color(t_diffuse_param p)
{
	t_tangetnt_map	map;
	int				pattern_a;

	map = get_tangent_coordinate_map(p.its_p);
	pattern_a = (int)(floor(map.u * CHECKER_U_MAG) + floor(map.v * CHECKER_V_MAG)) % 2;
	if (pattern_a)
		return (p.its_p->obj->obj_color.checker_color);
	return (p.its_p->obj->obj_color.kd);
}
