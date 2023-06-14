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

void	outerproduct_ready(t_vec *d_n_oupro, t_vec *ac_n_oupro, \
t_ray *eye2scr, t_cylinder *cylinder)
{
	t_vec	eye2cylinderbottom;

	calc_outerproduct(d_n_oupro, &eye2scr->unit_dir, &cylinder->axis);
	neg_vec(&eye2cylinderbottom, &eye2scr->pos, &cylinder->bottom_center);
	calc_outerproduct(ac_n_oupro, &eye2cylinderbottom, &cylinder->axis);
}

double	calc_cylinderratio(t_obj *obj, t_ray *eye2scr, \
t_intersection_point *itsp)
{
	t_cylinder	cylinder;
	t_vec		d_n;
	t_vec		ac_n;
	double		t2;
	double		t1;

	cylinder = obj->shape_data.cylinder;
	itsp->obj = obj;
	itsp->obj->obj_color = obj->obj_color;
	outerproduct_ready(&d_n, &ac_n, eye2scr, &cylinder);
	t2 = check_intersection_t2(&d_n, &ac_n, &cylinder, eye2scr);
	if (t2 >= 0.0)
		set_intersection_t2(itsp, t2, &cylinder, eye2scr);
	t1 = check_intersection_t1(&d_n, &ac_n, &cylinder, eye2scr);
	if (t1 - 0 >= EPSIRON)
	{
		set_intersection_t1(itsp, t1, &cylinder, eye2scr);
		return (t1);
	}
	if (t2 >= 0.0)
		return (t2);
	return (-1.0);
}
