/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_with_corn.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:25:59 by user              #+#    #+#             */
/*   Updated: 2023/05/17 22:26:01 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_corn_ints	calc_ints(t_corn *c, t_ray r, t_corn_param p, double t)
{
	t_corn_ints	ints;

	ints.vec_ti_d = k_vec(t, r.unit_dir);
	ints.vec_pos = add(r.pos, ints.vec_ti_d);
	ints.vec_pos_po = sub(ints.vec_pos_po, c->origin);
	ints.vec_norm_pos_po = norm_vec(ints.vec_pos_po);
	ints.vec_normal = vec_k1v1_k2v2(\
					norm(p.vec_inv_axis) * p.half_of_vertex_angle, \
					ints.vec_norm_pos_po, \
					-1.0, p.vec_inv_axis);
	ints.h = dot(ints.vec_pos, c->axis);
	return (ints);
}

// 円錐面はorigin(先端)から上下に広がる。
// 先端が上向き（下方向に伸びる円錐面）の有効範囲は、cornの高さをHとすると -H <= h <= 0
// corn->axisを底面から先端方向に定義
static bool	is_in_range_corn_height(double t, double intp_h, double corn_h)
{
	if (0.0 < t)
		return (false);
	if (0 <= intp_h && intp_h <= corn_h)
		return (true);
	return (false);
}

static void	assign_intp_info(t_intersection_point *ret_intp, \
								t_corn_ints ints, double t)
{
	ret_intp->distance = t;
	ret_intp->position = ints.vec_pos;
	ret_intp->normal = ints.vec_normal;
}

static t_intersection_point	calc_intp_info_of_corn(t_corn *corn, t_ray ray, \
													t_corn_param p, t_d_param d)
{
	t_intersection_point	ret_intp;
	const t_corn_ints		ints_t1 = calc_ints(corn, ray, p, d.t1);
	const t_corn_ints		ints_t2 = calc_ints(corn, ray, p, d.t2);

	ret_intp.distance = -1.0;
	if (is_in_range_corn_height(d.t1, ints_t1.h, corn->height))
		assign_intp_info(&ret_intp, ints_t1, d.t1);
	else if (is_in_range_corn_height(d.t2, ints_t2.h, corn->height))
	{
		assign_intp_info(&ret_intp, ints_t2, d.t2);
		ret_intp.normal = inverse(ret_intp.normal);
	}
	return (ret_intp);
}

double	calc_intersect_with_corn(t_obj *obj, t_ray ray, \
									t_intersection_point *intp)
{
	t_corn			*corn;
	t_corn_param	intp_param;
	t_d_param		d_param;

	corn = &obj->shape_data.corn;
	intp_param = calc_inpt_param_of_corn(corn, ray);
	d_param = calc_d_param_of_corn(intp_param);
	d_param.d = calc_discriminant(d_param.a, d_param.b, d_param.c);
	if (d_param.a == 0.0 || d_param.d < 0.0)
		return (-1.0);
	solve_quadratic_equation(&d_param);
	if ((d_param.t1 <= 0.0 && d_param.t2 <= 0) || !intp)
		return (-1.0);
	*intp = calc_intp_info_of_corn(corn, ray, intp_param, d_param);
	(*intp).obj = obj;
	return (intp->distance);
}
