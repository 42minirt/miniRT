/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcratio_cyliunder_helper.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 01:08:13 by user              #+#    #+#             */
/*   Updated: 2023/06/14 01:08:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	calc_discreminant(double a, double b, double c)
{
	double	d_di;

	d_di = pow(b, 2.0) - 4.0 * a * c;
	if (d_di < 0)
		return (-1.0);
	return (d_di);
}

void	set_intersection_t2(t_intersection_point *itp, \
							double t, \
							t_cylinder *cyl, \
							t_ray *ray)
{
	t_vec	center2its;
	t_vec	axis_size_vec;
	t_vec	normal_timessize;

	itp->distance = t;
	itp->position = vec_k1v1_k2v2(1, ray->pos, t, ray->unit_dir);
	neg_vec(&center2its, &itp->position, &cyl->bottom_center);
	times_vec(&axis_size_vec, dot_vec(&center2its, &cyl->axis), &cyl->axis);
	neg_vec(&normal_timessize, &axis_size_vec, &center2its);
	normalize(&itp->normal, &normal_timessize);
}

double	check_intersection_t2(t_vec *d_n, \
								t_vec *ac_n, \
								t_cylinder *cyl, \
								t_ray *ray)
{
	double	d_di;
	t_vec	eye2its;
	t_vec	bottom2its;
	double	t;

	if (obtain_vecsize(d_n) - 0.0 < EPSIRON)
		return (-1.0);
	d_di = calc_discreminant(\
	pow(obtain_vecsize(d_n), 2), \
	2.0 * dot_vec(d_n, ac_n), \
	pow(obtain_vecsize(ac_n), 2.0) - pow(cyl->radius, 2.0) \
	);
	if (d_di < 0.0)
		return (-1.0);
	t = (-1.0 * 2.0 * dot_vec(d_n, ac_n) + sqrt(d_di)) \
	/ (2.0 * pow(obtain_vecsize(d_n), 2));
	eye2its = vec_k1v1_k2v2(1, ray->pos, t, ray->unit_dir);
	neg_vec(&bottom2its, &eye2its, &cyl->bottom_center);
	if (0 <= dot_vec(&bottom2its, &cyl->axis) \
	&& dot_vec(&bottom2its, &cyl->axis) <= cyl->height \
	&& t >= 0.0)
		return (t);
	return (-1.0);
}

void	set_intersection_t1(t_intersection_point *itp, \
								double t, \
								t_cylinder *cyl, \
								t_ray *ray)
{
	t_vec	center2its;
	t_vec	axis_size_vec;
	t_vec	normal_timessize;

	itp->distance = t;
	itp->position = vec_k1v1_k2v2(1, ray->pos, t, ray->unit_dir);
	neg_vec(&center2its, &itp->position, &cyl->bottom_center);
	times_vec(&axis_size_vec, dot_vec(&center2its, &cyl->axis), &cyl->axis);
	neg_vec(&normal_timessize, &center2its, &axis_size_vec);
	normalize(&itp->normal, &normal_timessize);
}

double	check_intersection_t1(t_vec *d_n, \
								t_vec *ac_n, \
								t_cylinder *cyl, \
								t_ray *ray)
{
	double	d_di;
	t_vec	eye2its;
	t_vec	bottom2its;
	double	t;

	if (obtain_vecsize(d_n) <= 0.0)
		return (-1.0);
	d_di = calc_discreminant(\
	pow(obtain_vecsize(d_n), 2), \
	2.0 * dot_vec(d_n, ac_n), \
	pow(obtain_vecsize(ac_n), 2) - pow(cyl->radius, 2) \
	);
	if (d_di <= 0.0)
		return (-1.0);
	t = (-1.0 * 2.0 * dot_vec(d_n, ac_n) - sqrt(d_di)) \
	/ (2.0 * pow(obtain_vecsize(d_n), 2));
	eye2its = vec_k1v1_k2v2(1, ray->pos, t, ray->unit_dir);
	neg_vec(&bottom2its, &eye2its, &cyl->bottom_center);
	if (0 <= dot_vec(&bottom2its, &cyl->axis) \
	&& dot_vec(&bottom2its, &cyl->axis) <= cyl->height \
	&& t >= 0)
		return (t);
	return (-1.0);
}
