#include "minirt.h"

static bool	is_in_range_spotlight(t_diffuse_param p)
{
	double	angle_pos2light;

	angle_pos2light = acos(dot(p.vec_light2pos, p.light->sl_dir)) * 180.0 / (2.0 * M_PI);
	if (angle_pos2light < 0)
		angle_pos2light *= -1.0; //todo: check
	return (angle_pos2light <= p.light->sl_angle);
}

t_color	get_diffuse_ref_color(t_diffuse_param p)
{
	t_color	ret_color;

	ret_color = init_color(0.0, 0.0, 0.0);
	if (is_image_data_exists(p.its_p->obj->obj_color))
		return (ret_color);
	if (p.dot_n_pos2light <= 0.0)
		return (ret_color);

	if (p.light->type == LT_POINT && !is_in_range_spotlight(p))
		return (ret_color);
	ret_color = color_k1c1_k2c2(1.0, p.its_p->obj->obj_color.kd, \
							p.dot_n_pos2light, p.light->light_color);
	return (ret_color);
}
