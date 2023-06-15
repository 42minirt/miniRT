/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rayvec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 00:42:09 by user              #+#    #+#             */
/*   Updated: 2023/06/14 21:31:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "raytrace.h"
#include "vector.h"

static double	to_radians(double deg)
{
	return (deg / 2.0 * M_PI / 180.0);
}

static double	calc_eye2scrcen_distance(t_camera_info *camera_info)
{
	return (WINDOW_WIDTH / (2.0 * tan(to_radians(camera_info->fov_deg))));
}

static void	ready_scr2world_ex(t_vec *scr2world_ex, t_camera_info *camera_info)
{
	double	sx;
	double	sz;
	double	dirx2_dirz2;

	dirx2_dirz2 = pow(camera_info->direction.x, 2) \
	+ pow(camera_info->direction.z, 2);
	if (dirx2_dirz2 == 0)
		setvec(scr2world_ex, 1.0, 0.0, 0.0);
	else
	{
		sx = camera_info->direction.z / (sqrt(dirx2_dirz2));
		sz = (-1.0) * camera_info->direction.x / (sqrt(dirx2_dirz2));
		setvec(scr2world_ex, sx, 0.0, sz);
	}
}

t_ray	red_rayvec(t_camera_info *camera_info, double x, double y)
{
	t_vec	eye2scr;
	t_vec	scr2world_ex;
	t_vec	scr2world_ey;
	t_vec	t_ray_vec;
	t_vec	t_ray_n;

	eye2scr = k_vec(calc_eye2scrcen_distance(camera_info), \
	camera_info->direction);
	ready_scr2world_ex(&scr2world_ex, camera_info);
	calc_outerproduct(&scr2world_ey, &camera_info->direction, &scr2world_ex);
	normalize(&scr2world_ey, &scr2world_ey);
	t_ray_vec = vec_k1v1_k2v2(1, vec_k1v1_k2v2(\
	1, \
	eye2scr, x - (WINDOW_WIDTH / 2.0), scr2world_ex), \
	(WINDOW_HEIGHT / 2.0) - y, \
	scr2world_ey);
	normalize(&t_ray_n, &t_ray_vec);
	camera_info->camera.unit_dir.x = t_ray_n.x;
	camera_info->camera.unit_dir.y = t_ray_n.y;
	camera_info->camera.unit_dir.z = t_ray_n.z;
	camera_info->camera.pos = camera_info->position;
	return (camera_info->camera);
}

/******************************^****************^******************************/
/*****************************^ ^**************^ ^*****************************/
/****************************^   ^aaaaaaaaaaaa^   ^****************************/
/**************************c                        c**************************/
/*************************c       @          @       c*************************/
/************************c                            c************************/
/***********************c       ===   |     ===       c************************/
/************************c      ===\__/\__/ ===      c*************************/
/*************************c          \__/           c***********satushi********/
/**************************catcatcatcatcatcatcatcatc***************************/