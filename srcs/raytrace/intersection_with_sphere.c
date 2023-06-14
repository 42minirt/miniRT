/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_with_sphere.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:25:56 by user              #+#    #+#             */
/*   Updated: 2023/06/11 17:54:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_d_param	calc_d_param_of_sphere(t_sphere *sphere, t_ray ray)
{
	t_vec		pe_pc;
	t_d_param	d_param;

	pe_pc = sub(ray.pos, sphere->center);
	d_param.a = dot(ray.unit_dir, ray.unit_dir);
	d_param.b = 2.0 * dot(ray.unit_dir, pe_pc);
	d_param.c = dot(pe_pc, pe_pc) - pow(sphere->radius, 2.0);
	return (d_param);
}

static t_intersection_point	calc_intp_info_of_shpere(t_sphere *sphere, \
														t_ray ray, \
														double t)
{
	t_intersection_point	intp;
	t_vec					td;

	intp.distance = t;
	td = k_vec(t, ray.unit_dir);
	intp.position = add(ray.pos, td);
	intp.normal = sub(intp.position, sphere->center);
	intp.normal = norm_vec(intp.normal);
	return (intp);
}

double	calc_intersect_with_sphere(t_obj *obj, \
									t_ray ray, \
									t_intersection_point *its_p)
{
	t_sphere				*sphere;
	t_d_param				d_param;
	t_intersection_point	tmp_its_p;
	double					t;

	sphere = &obj->shape_data.sphere;
	d_param = calc_d_param_of_sphere(sphere, ray);
	d_param.d = calc_discriminant(d_param.a, d_param.b, d_param.c);
	if (d_param.a == 0.0 || d_param.d < 0.0)
		return (-1.0);
	solve_quadratic_equation(&d_param);
	t = get_valid_distance(d_param.t1, d_param.t2);
	if (t <= 0.0)
		return (-1.0);
	tmp_its_p = calc_intp_info_of_shpere(sphere, ray, t);
	tmp_its_p.obj = obj;
	*its_p = tmp_its_p;
	return (its_p->distance);
}
