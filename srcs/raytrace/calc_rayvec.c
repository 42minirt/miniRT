/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rayvec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 00:42:09 by user              #+#    #+#             */
/*   Updated: 2023/05/28 20:12:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	calc_eye2scrcen_distance(t_camera_info *camera_info)
{
	return (WINDOW_WIDTH / (2.0 * tan(camera_info->fov_deg / 2 * M_PI / 180.0)));
}

void	ready_scr2world_ex(t_vec *scr2world_ex, t_camera_info *camera_info)
{
	double	sx; //スクリーン状のex成分のx成分
	double	sz; //スクリーン状のex成分のz成分
	double	dirx2_dirz2;

	dirx2_dirz2 = pow(camera_info->direction.x, 2) + pow(camera_info->direction.z, 2);
	if (dirx2_dirz2 == 0)
		setvec(scr2world_ex, -1.0, 0.0, 0);
	else
	{
		sx = camera_info->direction.z / (sqrt(dirx2_dirz2));
		sz = (-1.0) * camera_info->direction.x / (sqrt(dirx2_dirz2));
		// printf("%f\n", sx);
		// printf("%f\n", sz);
		setvec(scr2world_ex, sx, 0.0, sz);
	}
}

t_ray	red_rayvec(t_camera_info *camera_info, double x, double y)
{
	t_vec	eye2scr;
	t_vec	scr2world_ex;
	t_vec	scr2world_ey;
	t_vec	t_ray_vec;
	t_vec	t_ray_n;//ここはt_camera_infoの中の変数でいい気もする

	//視点からスクリーンまでの距離を求める
	//calc_eye2scrcen_distance
	//上記からeye2scr(の中心)のベクトルを求める
	eye2scr = k_vec(calc_eye2scrcen_distance(camera_info), camera_info->direction);
	//カメラの方向ベクトルを用いてスクリーンのx方向のベクトルを表現する
	ready_scr2world_ex(&scr2world_ex, camera_info);
	//スクリーンのy方向のベクトルをx方向のベクトルとカメラの方向ベクトルの外積で求める
	calc_outerproduct(&scr2world_ey, &camera_info->direction, &scr2world_ex);
	normalize(&scr2world_ey, &scr2world_ey);
	//t_rayというベクトルを求める（カメラからスクリーン状のある点までのベクトル）
	t_ray_vec = vec_k1v1_k2v2(1, vec_k1v1_k2v2(\
	1, \
	eye2scr, x - (WINDOW_WIDTH / 2.0), scr2world_ex), \
	(WINDOW_HEIGHT / 2.0) - y, \
	scr2world_ey);
	//t_rayをunit化して返す
	normalize(&t_ray_n, &t_ray_vec);

	//格納
	camera_info->camera.unit_dir.x = t_ray_n.x;
	camera_info->camera.unit_dir.y = t_ray_n.y;
	camera_info->camera.unit_dir.z = t_ray_n.z;

	camera_info->camera.pos = camera_info->position;

	//返す
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