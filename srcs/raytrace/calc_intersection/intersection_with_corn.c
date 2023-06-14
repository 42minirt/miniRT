/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_with_corn.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:25:59 by user              #+#    #+#             */
/*   Updated: 2023/06/11 17:54:21 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	is_in_range_corn_height(double t, double intp_h, double corn_h)
{
	if (0.0 < t && 0.0 <= intp_h && intp_h <= corn_h)
		return (true);
	return (false);
}

static void	assign_intp_info(t_intersection_point *ret_intp, \
								t_corn_ints ints, \
								double t)
{
	ret_intp->distance = t;
	ret_intp->position = ints.vec_pos;
	ret_intp->normal = ints.vec_normal;
}

static t_intersection_point	calc_intp_info_of_corn(t_corn *corn, \
													t_ray ray, \
													t_corn_param p, \
													t_d_param d)
{
	t_intersection_point	ret_intp;
	const t_corn_ints		ints_t1 = calc_ints(corn, ray, p, d.t1);
	const t_corn_ints		ints_t2 = calc_ints(corn, ray, p, d.t2);

	if (is_in_range_corn_height(d.t1, ints_t1.h, corn->height))
		assign_intp_info(&ret_intp, ints_t1, d.t1);
	else if (is_in_range_corn_height(d.t2, ints_t2.h, corn->height))
	{
		assign_intp_info(&ret_intp, ints_t2, d.t2);
		ret_intp.normal = inverse(ret_intp.normal);
	}
	else
		ret_intp.distance = -1.0;
	return (ret_intp);
}

double	calc_intersect_with_corn(t_obj *obj, \
									t_ray ray, \
									t_intersection_point *its_p)
{
	t_corn					*corn;
	t_corn_param			intp_param;
	t_intersection_point	tmp_its_p;
	t_d_param				d_param;

	corn = &obj->shape_data.corn;
	intp_param = calc_ints_param_of_corn(corn, ray);
	d_param = calc_d_param_of_corn(intp_param);
	d_param.d = calc_discriminant(d_param.a, d_param.b, d_param.c);
	if (d_param.a == 0.0 || d_param.d < 0.0)
		return (-1.0);
	solve_quadratic_equation(&d_param);
	if (d_param.t1 <= 0.0 && d_param.t2 <= 0.0)
		return (-1.0);
	tmp_its_p = calc_intp_info_of_corn(corn, ray, intp_param, d_param);
	tmp_its_p.obj = obj;
	*its_p = tmp_its_p;
	return (its_p->distance);
}
