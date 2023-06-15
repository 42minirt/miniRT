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

#include "raytrace.h"
#include "vector.h"

#define TMPEPSIRON (0.00000000000512)

bool	ch_conflict_sphere(t_sphere obj, t_vec pos)
{
	double	size_pos2center;
	t_vec	pos2center;

	neg_vec(&pos2center, &pos, &obj.center);
	size_pos2center = obtain_vecsize(&pos2center);
//	printf("obj(%f, %f, %f) vs pos(%f, %f, %f)\n",
//		   obj.center.x,obj.center.y,obj.center.z,
//		   pos.x, pos.y, pos.z);
	if (fabs(size_pos2center - obj.radius) <= (1.0 / EPSILON_DIVISOR))
		return (true);
	return (false);
}

static double	calc_differ_plane_helper2(double a, \
											double b, \
											double c, \
											double d)
{
	double	tmp;

	tmp = a + b + c + d;
	if (tmp < 0.0)
		return (-1.0 * tmp);
	return (tmp);
}

//https://hiraocafe.com/note/plane_equation.html こいつを使う
//分ぼは法線ベクトルを使用しているため0にはならないはずである
bool	ch_conflict_plane(t_plane obj, t_vec pos)
{
	double	differ_size;

	differ_size = calc_differ_plane_helper2(\
	obj.normal.x * pos.x, \
	obj.normal.y * pos.y, \
	obj.normal.z * pos.z, \
	obj.normal.x * (-1.0) * obj.center.x \
	+ obj.normal.y * (-1.0) * obj.center.y \
	+ obj.normal.z * (-1.0) * obj.center.z);
	if (differ_size - TMPEPSIRON < 0.0)
		return (true);
	return (false);
}

bool	ch_conflict_cylinder(t_cylinder obj, t_vec pos)
{
	t_vec	tmp;
	double	height;
	double	differsize;
	double	tmp_rad;

	neg_vec(&tmp, &pos, &obj.bottom_center);
	height = dot(tmp, obj.axis);
	differsize = obtain_vecsize(&tmp);
	tmp_rad = sqrt(pow(differsize, 2.0) - pow(height, 2.0));
	if (height < 0.0 || height > obj.height)
		return (false);
	if (tmp_rad - obj.radius - TMPEPSIRON < 0.0)
		return (true);
	return (false);
}

bool	ch_conflict_corn(t_corn obj, t_vec pos)
{
	t_vec	tmp;
	double	height;
	double	differsize;
	double	tmp_rad;
	double	tmp_num;

	neg_vec(&tmp, &pos, &obj.bottom_center);
	height = dot(tmp, obj.axis);
	differsize = obtain_vecsize(&tmp);
	tmp_rad = sqrt(pow(differsize, 2.0) - pow(height, 2.0));
	if (height < 0.0 || obj.height < height)
		return (false);
	if ((0 < tmp_rad && tmp_rad < TMPEPSIRON) \
	|| (tmp_rad < 0 && -1.0 * tmp_rad < TMPEPSIRON))
		return (true);
	tmp_num = obj.radius - (obj.height * tmp_rad / height);
	if ((tmp_num > 0 && tmp_num < TMPEPSIRON) \
	|| (tmp_num < 0 && -1.0 * tmp_num < TMPEPSIRON))
		return (true);
	return (false);
}
