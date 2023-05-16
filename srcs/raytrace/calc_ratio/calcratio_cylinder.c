/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcratio_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:23:55 by user              #+#    #+#             */
/*   Updated: 2023/05/16 20:00:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

double	calc_discreminant(double A, double B, double C)
{
	double	D;

	D = pow(B, 2) - 4.0 * A * C;
	if (D < 0)
		return (-1.0);
	return (D);
}

double	set_itsp(t_intersection_point *itp, double t, t_cylinder *cyl, t_ray *ray, int i)
{
	t_vec	normal;
	t_vec	position;
	t_vec	center2its;
	t_vec	axis_size_vec;
	t_vec	normal_timessize;

	itp->distance = t;
	t_mix_vec_all(&itp->position, 1, &ray->pos, t, &ray->unit_dir);
	neg_vec(&center2its, &itp->position, &cyl->bottom_center);
	times_vec(&axis_size_vec, dot_vec(&center2its, &cyl->axis), &cyl->axis);
	if (i == 1)
		neg_vec(&normal_timessize, &center2its, &axis_size_vec);
	else
		neg_vec(&normal_timessize, &axis_size_vec, &center2its);
	normalize(&itp->normal, &normal_timessize);
	itp->obj = cyl;
	return (t);
}

double	set_itp_befor(double t1, double t2, t_ray *ray, t_intersection_point *itsp, t_cylinder *cyl)
{
	t_vec	eye2its_t1;
	t_vec	eye2its_t2;
	t_vec	bottom12its;
	t_vec	bottom22its;

	t_mix_vec_all(&eye2its_t1, 1, &ray->pos, t1, &ray->unit_dir);
	t_mix_vec_all(&eye2its_t2, 1, &ray->pos, t2, &ray->unit_dir);
	//t1と交点を持つベクトルのaxis方向の大きさを調べる
	neg_vec(&bottom12its, &eye2its_t1, &cyl->bottom_center);
	neg_vec(&bottom22its, &eye2its_t2, &cyl->bottom_center);
	//サイズないならこっちが該当のもの
	if (0 <= dot_vec(&bottom12its, &cyl->axis) && dot_vec(&bottom12its, &cyl->axis) <= cyl->height)
		return (set_itsp(itsp, t1, cyl, ray, 1));
	else if (0 <= dot_vec(&bottom22its, &cyl->axis) && dot_vec(&bottom22its, &cyl->axis) <= cyl->height)
		return (set_itsp(itsp, t2, cyl, ray, 2));
	return (-1.0);
}

double	set_intersection(t_vec *d_n, t_vec *ac_n, t_cylinder *cyl, t_ray *ray, t_intersection_point *itsp) //名前をもう少し考えたい
{
	double	A;
	double	B;
	double	D;
	double	t1;
	double	t2;

	if (obtain_vecsize(d_n) == 0.0) //ここはイプシロンを用いたチェックが必要かも
		return (-1.0);
	A = pow(obtain_vecsize(d_n), 2);
	B = 2.0 * dot_vec(d_n, ac_n);
	D = calc_discreminant(A, B, pow(obtain_vecsize(&ac_n), 2) - pow(cyl->radius, 2));
	if (D < 0.0)
		return (-1.0);
	t1 = -1.0 * B + sqrt(D) / (2.0 * A);
	t2 = -1.0 * B - sqrt(D) / (2.0 * A);
	return (set_itp_befor(t1, t2, ray, itsp, cyl));// t1とt2で近い方のtを設定してitsを設定する
}

double	check_intersection_cylinder(t_ray *eye2scr, t_cylinder *cylinder, t_vec axis, t_intersection_point *itsp)
{
	t_vec	d_n_oupro;
	t_vec	eye2cylinderbottom;
	t_vec	ac_n_oupro;

	calc_outerproduct(&d_n_oupro, &eye2scr->unit_dir, &axis);
	neg_vec(&eye2cylinderbottom, &eye2scr->pos, &cylinder->bottom_center);
	calc_outerproduct(&ac_n_oupro, &eye2cylinderbottom, &axis);
	if (obtain_vecsize(&d_n_oupro) == 0.0)
		return (-1.0);
	return (set_intersection(&d_n_oupro, &ac_n_oupro, cylinder, eye2scr, itsp));
}

double	calc_cylinderratio(t_obj *obj, t_all_info *info, t_ray *eye2scr, t_intersection_point *tmp_itsp)
{
	t_vec		eye_direction;
	t_cylinder	*cylinder;
	double		t;

	tmp_itsp = NULL;
	eye_direction = eye2scr->unit_dir;
	cylinder = (t_cylinder *)obj;
	return (check_intersection_cylinder(eye2scr, cylinder, cylinder->axis, tmp_itsp));
}