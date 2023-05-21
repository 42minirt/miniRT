/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcratio_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:23:55 by user              #+#    #+#             */
/*   Updated: 2023/05/21 20:17:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

double	calc_discreminant(double A, double B, double C)
{
	double	D;

	D = pow(B, 2) - 4.0 * A * C;
	if (D < 0)
		return (-1.0);
	return (D);
}

double	select_t(double t, t_ray *ray, t_cylinder *cyl, int *i)
{
	t_vec	eye2its;
	t_vec	bottom2its;

	(void)i;
	t_mix_vec_all(&eye2its, 1, &ray->pos, t, &ray->unit_dir);
	neg_vec(&bottom2its, &eye2its, &cyl->bottom_center);
	if (0 <= dot_vec(&bottom2its, &cyl->axis) && dot_vec(&bottom2its, &cyl->axis) <= cyl->height)
		return (t);
	return (-1);
}

void	set_intersection_t2(t_intersection_point *itp, double t, t_cylinder *cyl, t_ray *ray)
{
	t_vec	center2its;
	t_vec	axis_size_vec;
	t_vec	normal_timessize;

	itp->distance = t;
	t_mix_vec_all(&itp->position, 1, &ray->pos, t, &ray->unit_dir);
	neg_vec(&center2its, &itp->position, &cyl->bottom_center);
	times_vec(&axis_size_vec, dot_vec(&center2its, &cyl->axis), &cyl->axis);
	neg_vec(&normal_timessize, &axis_size_vec, &center2its);
	normalize(&itp->normal, &normal_timessize);
}

double	check_intersection_t2(t_vec *d_n, t_vec *ac_n, t_cylinder *cyl, t_ray *ray) //名前をもう少し考えたい
{
	double	D;
	t_vec	eye2its;
	t_vec	bottom2its;
	double	t;

	if (obtain_vecsize(d_n) == 0.0) //ここはイプシロンを用いたチェックが必要かも
		return (-1.0);
	D = calc_discreminant(
		pow(obtain_vecsize(d_n), 2), 
		2.0 * dot_vec(d_n, ac_n), 
		pow(obtain_vecsize(ac_n), 2) - pow(cyl->radius, 2)
	);
	if (D < 0.0)
		return (-1.0);
	t = -1.0 * 2.0 * dot_vec(d_n, ac_n) + sqrt(D) / (2.0 * pow(obtain_vecsize(d_n), 2));
	t_mix_vec_all(&eye2its, 1, &ray->pos, t, &ray->unit_dir);
	neg_vec(&bottom2its, &eye2its, &cyl->bottom_center);
	if (0 <= dot_vec(&bottom2its, &cyl->axis) && dot_vec(&bottom2its, &cyl->axis) <= cyl->height)
		return (t);
	return (-1.0);
}

void	set_intersection_t1(t_intersection_point *itp, double t, t_cylinder *cyl, t_ray *ray)
{
	t_vec	center2its;
	t_vec	axis_size_vec;
	t_vec	normal_timessize;

	itp->distance = t;
	t_mix_vec_all(&itp->position, 1, &ray->pos, t, &ray->unit_dir);
	neg_vec(&center2its, &itp->position, &cyl->bottom_center);
	times_vec(&axis_size_vec, dot_vec(&center2its, &cyl->axis), &cyl->axis);
	neg_vec(&normal_timessize, &center2its, &axis_size_vec);
	normalize(&itp->normal, &normal_timessize);
}

double	check_intersection_t1(t_vec *d_n, t_vec *ac_n, t_cylinder *cyl, t_ray *ray) //名前をもう少し考えたい
{
	double	D;
	t_vec	eye2its;
	t_vec	bottom2its;
	double	t;

	if (obtain_vecsize(d_n) == 0.0) //ここはイプシロンを用いたチェックが必要かも
		return (-1.0);
	D = calc_discreminant(
		pow(obtain_vecsize(d_n), 2), 
		2.0 * dot_vec(d_n, ac_n), 
		pow(obtain_vecsize(ac_n), 2) - pow(cyl->radius, 2)
	);
	if (D < 0.0)
		return (-1.0);
	t = -1.0 * 2.0 * dot_vec(d_n, ac_n) + sqrt(D) / (2.0 * pow(obtain_vecsize(d_n), 2));
	t_mix_vec_all(&eye2its, 1, &ray->pos, t, &ray->unit_dir);
	neg_vec(&bottom2its, &eye2its, &cyl->bottom_center);
	if (0 <= dot_vec(&bottom2its, &cyl->axis) && dot_vec(&bottom2its, &cyl->axis) <= cyl->height)
		return (t);
	return (-1.0);
}

void	outerproduct_ready(t_vec *d_n_oupro, t_vec *ac_n_oupro, t_ray *eye2scr, t_cylinder *cylinder)
{
	t_vec	eye2cylinderbottom;

	calc_outerproduct(d_n_oupro, &eye2scr->unit_dir, &cylinder->axis);
	neg_vec(&eye2cylinderbottom, &eye2scr->pos, &cylinder->bottom_center);
	calc_outerproduct(ac_n_oupro, &eye2cylinderbottom, &cylinder->axis);
}

double	calc_cylinderratio(t_obj *obj, t_ray *eye2scr, t_intersection_point *itsp)
{
	t_cylinder	*cylinder;
	t_vec		d_n;
	t_vec		ac_n;
	double		t;

	itsp = NULL;
	cylinder = (t_cylinder *)obj;
	itsp->obj = obj;
	outerproduct_ready(&d_n, &ac_n, eye2scr, cylinder);
	t = check_intersection_t1(&d_n, &ac_n, cylinder, eye2scr);
	if (t >= 0.0)
	{
		set_intersection_t1(itsp, t, cylinder, eye2scr);
		return (t);
	}
	t = check_intersection_t2(&d_n, &ac_n, cylinder, eye2scr);
	if (t >= 0.0)
	{
		set_intersection_t2(itsp, t, cylinder, eye2scr);
		inverse_vec(&itsp->normal, &itsp->normal);
		return (t);
	}
	if (t >= 0.0)
		return (t);
	return (-1.0);
}