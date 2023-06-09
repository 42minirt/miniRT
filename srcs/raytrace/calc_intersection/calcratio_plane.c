/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcratio_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:24:08 by user              #+#    #+#             */
/*   Updated: 2023/06/14 01:00:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "vector.h"

static double	set_itsp(t_plane *plane, \
							double t, \
							t_ray *ray, \
							t_intersection_point *itsp)
{
	t_vec	eye2its;

	itsp->distance = t;
	itsp->normal.x = plane->normal.x;
	itsp->normal.y = plane->normal.y;
	itsp->normal.z = plane->normal.z;
	times_vec(&eye2its, t, &ray->unit_dir);
	add_vec(&itsp->position, &ray->pos, &eye2its);
	return (t);
}

double	calc_planeratio(t_obj *obj, \
						t_ray *ray, \
						t_intersection_point *itsp)
{
	t_plane	plane;
	double	p_n;
	double	e_n;
	double	dis_n;
	double	t;

	plane = obj->shape_data.plane;
	dis_n = dot(ray->unit_dir, plane.normal);
	p_n = dot(plane.center, plane.normal);
	e_n = dot(ray->pos, plane.normal);
	if (dis_n == 0.0)
		return (-1.0);
	t = (p_n - e_n) / dis_n;
	if (t <= 0.0)
		return (-1.0);
	else
	{
		itsp->obj = obj;
		itsp->obj->obj_color = obj->obj_color;
		return (set_itsp(&plane, t, ray, itsp));
	}
}
