/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rayvec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 00:42:09 by user              #+#    #+#             */
/*   Updated: 2023/05/26 11:42:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	calc_eye2scrcen_distance(t_camera_info *camera_info)
{
	return (WINDOW_WIDTH / (2.0 * camera_info->fov_deg));
}

void	ready_scr2world_ex(t_vec *scr2world_ex, t_camera_info *camera_info)
{
	
}

t_ray	red_rayvec(t_camera_info *camera_info, double x, double y)
{
	t_vec	eye2scr;
	t_vec	scr2world_ex;
	t_vec	scr2world_ey;
	t_vec	t_ray;
	t_vec	t_rey_n;//ここはt_camera_infoの中の変数でいい気もする

	//視点からスクリーンまでの距離を求める
	//calc_eye2scrcen_distance
	//上記からeye2scr(の中心)のベクトルを求める
	eye2scr = k_vec(calc_eye2scrcen_distance(camera_info), camera_info->direction);
	//カメラの方向ベクトルを用いてスクリーンのx方向のベクトルを表現する
	ready_scr2world_ex(&scr2world_ex, camera_info);
	//スクリーンのy方向のベクトルをx方向のベクトルとカメラの方向ベクトルの外積で求める

	//t_rayというベクトルを求める（カメラからスクリーン状のある点までのベクトル）

	//t_rayをunit化して返す
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