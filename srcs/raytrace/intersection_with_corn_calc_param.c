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

t_corn_param	calc_inpt_param_of_corn(t_corn *c, t_ray ray)
{
	t_corn_param	param;

	param.vec_pe_po = sub(ray.pos, c->origin);
	param.vec_cross_de_n = cross(ray.unit_dir, c->axis);
	param.vec_cross_pepo_n = cross(param.vec_pe_po, c->axis);
	param.vec_two_x_cross_de_n = k_vec(2, param.vec_cross_de_n);
	param.vec_inv_axis = inverse(c->axis);
	param.ratio_r_h = c->radius / c->height;
	param.half_of_vertex_angle = atan(param.ratio_r_h);
	param.dot_de_n = dot(ray.unit_dir, c->axis);
	param.dot_pepo_n = dot(param.vec_pe_po, c->axis);
	param.vec_norm_de_x_n = norm(param.vec_cross_de_n);
	param.vec_norm_pepo_x_n = norm(param.vec_cross_pepo_n);
	return (param);
}

t_d_param	calc_d_param_of_corn(t_corn_param p)
{
	t_d_param	d_param;

	d_param.a = pow(p.vec_norm_de_x_n, 2) \
				- pow(p.ratio_r_h, 2) * pow(p.dot_de_n, 2);
	d_param.b = dot(p.vec_two_x_cross_de_n, p.vec_cross_pepo_n) \
 				- 2 * pow(p.ratio_r_h, 2) * p.dot_de_n * p.dot_de_n;
	d_param.c = pow(p.vec_norm_pepo_x_n, 2) \
				- pow(p.ratio_r_h, 2) * pow(p.dot_pepo_n, 2);
	return (d_param);
}
