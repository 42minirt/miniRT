/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tangent_coordinate_map.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:24:07 by takira            #+#    #+#             */
/*   Updated: 2023/06/14 01:51:34 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "raytrace.h"
#include "vector.h"
#include "matrix.h"

// 0 <= u <= 1
// 0 <= v <= 1

static t_tangetnt_map	get_planer_map(t_intersection_point *its_p)
{
	t_tangetnt_map	map;
	t_vec			pos_local;
	t_vec			pos_uv;
	t_matrix		trans_mat_world2tangent;

	pos_local = sub(its_p->position, its_p->obj->shape_data.plane.center);
	trans_mat_world2tangent \
		= get_trans_mat_world2local_yup(its_p->normal);
	pos_uv = mul_matrix_vec(trans_mat_world2tangent, pos_local);
	map.u = pos_uv.x;
	map.v = -1.0 * pos_uv.z;
	return (map);
}

static t_tangetnt_map	get_spherical_map(t_intersection_point *its_p)
{
	t_tangetnt_map	map;
	t_vec			pos_local;
	double			azimuth_angle_phi;
	double			elevation_angle_theta;

	pos_local = sub(its_p->position, its_p->obj->shape_data.sphere.center);
	azimuth_angle_phi = atan2(pos_local.z, pos_local.x);
	elevation_angle_theta \
		= acos(pos_local.y / its_p->obj->shape_data.sphere.radius);
	map.u = (azimuth_angle_phi + M_PI * 3.0 / 2.0) / (2.0 * M_PI);
	map.v = elevation_angle_theta / M_PI;
	return (map);
}

static t_tangetnt_map	get_polar_coordinate_map(t_vec pos_local, \
													t_vec axis, \
													double size)
{
	t_tangetnt_map	map;
	t_vec			pos_uv;
	t_matrix		tarns_mat_world2tangent;
	double			azimuth_angle_phi;

	tarns_mat_world2tangent \
	= get_trans_mat_world2local_w_basis(axis);
	pos_uv = mul_matrix_vec(tarns_mat_world2tangent, pos_local);
	azimuth_angle_phi = atan2(pos_uv.z, pos_uv.x);
	map.u = azimuth_angle_phi / (2.0 * M_PI);
	map.v = -1.0 * pos_uv.y / size;
	return (map);
}

static t_tangetnt_map	get_cylindrical_map(t_intersection_point *its_p)
{
	t_tangetnt_map	map;
	t_vec			pos_local;
	t_vec			bottom_center;
	t_vec			axis;
	double			height;

	if (streq(its_p->obj->id_str, ID_CYLINDER))
	{
		bottom_center = its_p->obj->shape_data.cylinder.bottom_center;
		pos_local = sub(its_p->position, bottom_center);
		axis = its_p->obj->shape_data.cylinder.axis;
		height = its_p->obj->shape_data.cylinder.height;
	}
	else
	{
		bottom_center = its_p->obj->shape_data.corn.bottom_center;
		pos_local = sub(its_p->position, bottom_center);
		axis = its_p->obj->shape_data.corn.axis;
		height = its_p->obj->shape_data.corn.height;
	}
	map = get_polar_coordinate_map(pos_local, axis, height);
	return (map);
}

t_tangetnt_map	get_tangent_coordinate_map(t_intersection_point *its_p)
{
	t_tangetnt_map		map;

	if (streq(its_p->obj->id_str, ID_PLANE))
		map = get_planer_map(its_p);
	else if (streq(its_p->obj->id_str, ID_SPHERE))
		map = get_spherical_map(its_p);
	else
		map = get_cylindrical_map(its_p);
	return (map);
}
