/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_with_sphere.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:25:56 by user              #+#    #+#             */
/*   Updated: 2023/05/17 22:25:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_d_param	calc_d_param_of_sphere(t_sphere *sphere, t_ray ray)
{
	t_vec		pe_pc;
	t_d_param	d_param;

	neg_vec(&pe_pc, &ray.pos, &sphere->center);
	d_param.a = dot_vec(&ray.unit_dir, &ray.unit_dir);
	d_param.b = 2.0 * dot_vec(&ray.unit_dir, &pe_pc);
	d_param.c = dot_vec(&pe_pc, &pe_pc) - pow(sphere->radius, 2);
	return (d_param);
}

static t_intersection_point	calc_intp_info_of_shpere(t_sphere *sphere, \
													t_ray ray, double t)
{
	t_intersection_point	intp;
	t_vec					td;

	intp.distance = t;
	td = k_vec(t, ray.unit_dir);
	add_vec(&intp.position, &ray.pos, &td);
	neg_vec(&intp.normal, &intp.position, &sphere->center);
	normalize(&intp.normal, &intp.normal);
	return (intp);
}

double	calc_intersect_with_sphere(t_sphere *sphere, \
									t_ray ray, t_intersection_point *intp)
{
	t_d_param	d_param;
	double		t;

	d_param = calc_d_param_of_sphere(sphere, ray);
	d_param.d = calc_discriminant(d_param.a, d_param.b, d_param.c);
	if (d_param.a == 0.0 || d_param.d < 0.0)
		return (-1.0);
	solve_quadratic_equation(&d_param);
	t = get_valid_distance(d_param.t1, d_param.t2);
	if (t <= 0.0 || !intp)
		return (-1.0);
	*intp = calc_intp_info_of_shpere(sphere, ray, t);
	return (intp->distance);
}
