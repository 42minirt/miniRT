#include "minirt.h"

t_corn_param	calc_inpt_param_of_corn(t_corn *c, t_ray ray)
{
	t_corn_param	param;

	param.pe_po = sub(ray.pos, c->origin);
	param.cross_de_n = cross(ray.unit_dir, c->axis);
	param.cross_pepo_n = cross(param.pe_po, c->axis);
	param.two_x_cross_de_n = k_vec(2, param.cross_de_n);
	param.inv_axis = inverse(c->axis);
	param.ratio_r_h = c->radius / c->height;
	param.half_of_vertex_angle = atan(param.ratio_r_h);
	param.dot_de_n = dot(ray.unit_dir, c->axis);
	param.dot_pepo_n = dot(param.pe_po, c->axis);
	param.norm_de_x_n = norm(param.cross_de_n);
	param.norm_pepo_x_n = norm(param.cross_pepo_n);
	return (param);
}

t_d_param	calc_d_param_of_corn(t_corn_param p)
{
	t_d_param	d_param;

	d_param.a = pow(p.norm_de_x_n, 2) \
				- pow(p.ratio_r_h, 2) * pow(p.dot_de_n, 2);
	d_param.b = dot(p.two_x_cross_de_n, p.cross_pepo_n) \
				- 2 * pow(p.ratio_r_h, 2) * p.dot_de_n * p.dot_de_n;
	d_param.c = pow(p.norm_pepo_x_n, 2) \
				- pow(p.ratio_r_h, 2) * pow(p.dot_pepo_n, 2);
	return (d_param);
}
