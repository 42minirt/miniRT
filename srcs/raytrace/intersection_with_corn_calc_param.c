/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_with_corn_calc_param.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:26:03 by user              #+#    #+#             */
/*   Updated: 2023/05/17 22:26:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_corn_param	calc_ints_param_of_corn(t_corn *c, t_ray ray)
{
	t_corn_param	param;

	param.vec_origin2pe = sub(ray.pos, c->origin);
	param.vec_n = inverse(c->axis);
	param.vec_cross_de_n = cross(ray.unit_dir, param.vec_n);
	param.vec_cross_origin2pe_n = cross(param.vec_origin2pe, param.vec_n);
	param.ratio_r_h = c->radius / c->height;
	param.half_of_vertex_angle = atan(param.ratio_r_h);
	param.dot_de_n = dot(ray.unit_dir, param.vec_n);
	param.dot_origin2pe_n = dot(param.vec_origin2pe, param.vec_n);
	param.vec_norm_de_x_n = norm(param.vec_cross_de_n);
	param.norm_cross_origin2pe_x_n = norm(param.vec_cross_origin2pe_n);
	return (param);
}

t_d_param	calc_d_param_of_corn(t_corn_param p)
{
	t_d_param	d_param;

	d_param.a = pow(p.vec_norm_de_x_n, 2) \
 - pow(p.ratio_r_h, 2) * pow(p.dot_de_n, 2);
	d_param.b = 2.0 * dot(p.vec_cross_de_n, p.vec_cross_origin2pe_n) \
 - 2.0 * pow(p.ratio_r_h, 2) * p.dot_de_n * p.dot_origin2pe_n;
	d_param.c = pow(p.norm_cross_origin2pe_x_n, 2) \
 - pow(p.ratio_r_h, 2) * pow(p.dot_origin2pe_n, 2);
	return (d_param);
}

t_corn_ints	calc_ints(t_corn *corn, t_ray ray, t_corn_param p, double t)
{
	t_corn_ints	ints;

	ints.vec_pos = add(ray.pos, k_vec(t, ray.unit_dir));
	ints.vec_origin2pos = sub(ints.vec_pos, corn->origin);
	ints.vec_norm_origin2pos = norm_vec(ints.vec_origin2pos);
	ints.vec_normal = vec_k1v1_k2v2(\
					norm(p.vec_n) * cos(p.half_of_vertex_angle), \
					ints.vec_norm_origin2pos, \
					1.0, corn->axis);
	ints.vec_normal = norm_vec(ints.vec_normal);
	ints.h = dot(ints.vec_origin2pos, p.vec_n);
	return (ints);
}
