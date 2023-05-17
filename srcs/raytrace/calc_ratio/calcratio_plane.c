/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcratio_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:24:08 by user              #+#    #+#             */
/*   Updated: 2023/05/16 22:34:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	set_itsp(t_plane *plane, double t, t_ray *ray, t_intersection_point *itsp)
{
	t_vec	eye2its;

	if (t >= 0)
	{
		itsp->distance = t;
		itsp->normal = plane->center;
		itsp->obj = (t_shape_data *)plane;
		times_vec(&eye2its, t, &ray->unit_dir);
		add_vec(&itsp->position, &ray->pos, &eye2its);
	}
	return (t);
}

double	calc_planeratio(t_obj *obj, t_all_info *info, t_ray *ray, t_intersection_point *itsp)
{
	t_plane	*plane;
	t_vec	pos2center;
	double	n_pos2center;
	double	dis_n;

	plane = (t_plane *)obj;
	neg_vec(&pos2center, &plane->center, &ray->pos);
	n_pos2center = dot(plane->normal, pos2center);
	dis_n = dot(ray->unit_dir, plane->normal);
	return (set_itsp(plane, n_pos2center / dis_n, ray, itsp));
}