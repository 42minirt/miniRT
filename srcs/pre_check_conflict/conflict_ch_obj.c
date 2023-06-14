/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conflict_ch_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:56:45 by user              #+#    #+#             */
/*   Updated: 2023/06/14 21:40:52 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define TMPEPSIRON 0.00000000000512

bool	ch_conflict_spere(t_sphere obj, t_light	*light_info)
{
	double	differ_size;
	t_vec	tmp;

	neg_vec(&tmp, &light_info->point, &obj.center);
	differ_size = obtain_vecsize(&tmp);
	if (differ_size - obj.radius - TMPEPSIRON < 0)
		return (true);
	return (false);
}

double	calc_differ_plane_helper2(double a, double b, double c, double d)
{
	double	tmp;

	tmp = a + b + c + d;
	if (tmp < 0.0)
		return (-1.0 * tmp);
	return (tmp);
}

//https://hiraocafe.com/note/plane_equation.html こいつを使う
//分ぼは法線ベクトルを使用しているため0にはならないはずである
bool	ch_conflict_plane(t_plane obj, t_light	*light_info)
{
	double	differ_size;

	(void)light_info;
	differ_size = calc_differ_plane_helper2(obj.normal.x \
	* light_info->point.x, obj.normal.y * \
	light_info->point.y, obj.normal.z * light_info->point.z, \
	obj.normal.x * (-1.0) * obj.center.x + obj.normal.y * (-1.0) \
	* obj.center.y + obj.normal.z * (-1.0) * obj.center.z);
	if (differ_size - TMPEPSIRON < 0.0)
		return (true);
	return (false);
}

bool	ch_conflict_cylinder(t_cylinder obj, t_light	*light_info)
{
	t_vec	tmp;
	double	height_to_light;
	double	differsize;
	double	tmp_rad;

	neg_vec(&tmp, &light_info->point, &obj.bottom_center);
	height_to_light = dot(tmp, obj.axis);
	differsize = obtain_vecsize(&tmp);
	tmp_rad = sqrt(pow(differsize, 2.0) - pow(height_to_light, 2.0));
	if (height_to_light < 0.0 || height_to_light > obj.height)
		return (false);
	if (tmp_rad - obj.radius - TMPEPSIRON < 0.0)
		return (true);
	return (false);
}

bool	ch_conflict_corn(t_corn obj, t_light	*light_info)
{
	t_vec	tmp;
	double	height_to_light;
	double	differsize;
	double	tmp_rad;
	double	tmp_num;

	neg_vec(&tmp, &light_info->point, &obj.bottom_center);
	height_to_light = dot(tmp, obj.axis);
	differsize = obtain_vecsize(&tmp);
	tmp_rad = sqrt(pow(differsize, 2.0) - pow(height_to_light, 2.0));
	if (height_to_light < 0.0 || height_to_light > obj.height)
		return (false);
	if ((tmp_rad > 0 && tmp_rad < TMPEPSIRON) || \
	(tmp_rad < 0 && -1.0 * tmp_rad < TMPEPSIRON))
		return (true);
	tmp_num = obj.radius - (obj.height * tmp_rad / height_to_light);
	if ((tmp_num > 0 && tmp_num < TMPEPSIRON) || \
	(tmp_num < 0 && -1.0 * tmp_num < TMPEPSIRON))
		return (true);
	return (false);
}
