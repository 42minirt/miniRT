/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcratio_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:23:55 by user              #+#    #+#             */
/*   Updated: 2023/05/16 08:29:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

double	calc_discreminant(double A, double B, double C)
{

}

double	set_intersection(t_vec *d_n, t_vec *ac_n, t_cylinder *cyl, t_ray *ray, t_intersection_point *itsp) //名前をもう少し考えたい
{
	double	A;
	double	B;

	if (obtain_vecsize(d_n) == 0.0) //ここはイプシロンを用いたチェックが必要かも
		return (-1.0);
	A = pow(obtain_vecsize(d_n), 2);
	B = 2.0 * dot_vec(d_n, ac_n);
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
	t = check_intersection_cylinder(eye2scr, cylinder, cylinder->axis, tmp_itsp);
}