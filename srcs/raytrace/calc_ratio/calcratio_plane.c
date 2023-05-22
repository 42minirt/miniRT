/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcratio_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:24:08 by user              #+#    #+#             */
/*   Updated: 2023/05/22 21:15:31 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static void	set_vec(t_vec *sub, t_vec *tgt)
{
	sub->x = tgt->x;
	sub->y = tgt->y;
	sub->z = tgt->z;
}

double	set_itsp(t_plane *plane, double t, t_ray *ray, t_intersection_point *itsp)
{
	t_vec	eye2its;

	if (t >= 0)
	{
		itsp->distance = t;
		set_vec(&itsp->normal, &plane->normal);
		times_vec(&eye2its, t, &ray->unit_dir);
		add_vec(&itsp->position, &ray->pos, &eye2its);
	}
	return (t);
}

double	calc_planeratio(t_obj *obj, t_ray *ray, t_intersection_point *itsp)
{
	t_plane	*plane;
	t_vec	pos2center;
	double	n_pos2center;
	double	dis_n;
	double	t;

	plane = (t_plane *)obj;
	neg_vec(&pos2center, &ray->pos, &plane->center);
	n_pos2center = dot(plane->normal, pos2center);
	dis_n = dot(ray->unit_dir, plane->normal);
	t = set_itsp(plane, n_pos2center / dis_n, ray, itsp);
	if (t < 0)
		return (-1.0);
	else
	{
		itsp->obj = obj;
		itsp->obj->obj_color = obj->obj_color;
		return (t);
	}
}