#include "minirt.h"

#include "minirt.h"

static t_corn_param	calc_inpt_param_of_corn(t_corn *c, t_ray ray)
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
}

static t_d_param	calc_d_param_of_corn(t_corn_param p)
{
	t_d_param	d_param;

	d_param.a = pow(p.norm_de_x_n, 2)  - pow(p.ratio_r_h, 2) * pow(p.dot_de_n, 2);
	d_param.b = dot(p.two_x_cross_de_n, p.cross_pepo_n)  \
				- 2 * pow(p.ratio_r_h, 2) * p.dot_de_n * p.dot_de_n;
	d_param.c = pow(p.norm_pepo_x_n, 2) - pow(p.ratio_r_h, 2) * pow(p.dot_pepo_n, 2);
	return (d_param);
}

static t_corn_ints	calc_ints(t_corn *c, t_ray r, t_corn_param p, double t)
{
	t_corn_ints	ints;

	ints.ti_d = k_vec(t, r.unit_dir);
	ints.pos = add(r.pos, ints.ti_d);
	ints.pos_po = sub(ints.pos_po, c->origin);
	ints.norm_pos_po = norm_vec(ints.pos_po);
	ints.normal = vec_k1v1_k2v2(\
					norm(p.inv_axis) * p.half_of_vertex_angle, ints.norm_pos_po, \
					-1.0, p.inv_axis);
	ints.h = dot(ints.pos, c->axis);
}

// 円錐面はorigin(先端)から上下に広がる。
// 先端が上向き（下方向に伸びる円錐面）の有効範囲は、cornの高さをHとすると -H <= h <= 0
// corn->axisを底面から先端方向に定義
static bool	is_in_range_corn_height(double t, double intp_h, double corn_h)
{
	if (0.0 < t)
		return (false);
	if (0 <= intp_h && intp_h <= corn_h)
		return (true );
	return (false);
}

static void	assign_intp_info(t_intersection_point *ret, t_corn_ints ints, double t)
{
	ret->distance = t;
	ret->position = ints.pos;
	ret->normal = ints.normal;
}

static t_intersection_point	calc_intp_info_of_corn(t_corn *corn, t_ray ray, \
													t_corn_param p, t_d_param d)
{
	t_intersection_point	ret;
	const t_corn_ints		ints_t1 = calc_ints(corn, ray, p, d.t1);
	const t_corn_ints		ints_t2 = calc_ints(corn, ray, p, d.t2);

	ret.distance = -1.0;
	if (is_in_range_corn_height(d.t1, ints_t1.h, corn->height))
		assign_intp_info(&ret, ints_t1, d.t1);
	else if (is_in_range_corn_height(d.t2, ints_t2.h, corn->height))
	{
		assign_intp_info(&ret, ints_t2, d.t2);
		ret.normal = inverse(ret.normal);
	}
	return (ret);
}

double	calc_intersect_with_sphere(t_corn *corn, t_ray ray, t_intersection_point *intp)
{
	t_corn_param	intp_param;
	t_d_param		d_param;

	intp_param = calc_inpt_param_of_corn(corn, ray);
	d_param = calc_d_param_of_corn(intp_param);
	d_param.d = calc_discriminant(d_param.a, d_param.b, d_param.c);
	if (d_param.a == 0.0 || d_param.d < 0.0)
		return (-1.0);
	solve_quadratic_equation(&d_param);
	if ((d_param.t1 <= 0.0 && d_param.t2 <= 0) || !intp)
		return (-1.0);
	*intp = calc_intp_info_of_corn(corn, ray, intp_param, d_param);
	return (intp->distance);
}
