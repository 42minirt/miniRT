/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/18 17:44:29 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	alloc_info_ptr(t_all_info *all_info)
{
	all_info->mlx_info = ft_calloc(sizeof(t_mlx_info), 1);
	all_info->scene_info = ft_calloc(sizeof(t_scene_info), 1);
	all_info->camera_info = ft_calloc(sizeof(t_camera_info), 1);
	if (!all_info->mlx_info || !all_info->scene_info || !all_info->camera_info)
		return (FAILURE);
	all_info->scene_info->lights = NULL;
	all_info->scene_info->objs = NULL;
	all_info->scene_info->brightness = -1.0; // check for duplicate id
	all_info->camera_info->fov_deg = -1.0;   // check for duplicate id
	return (SUCCESS);
}

static int	init_mlx(t_mlx_info *mlx_info)
{
	mlx_info->mlx = mlx_init();
	if (!mlx_info->mlx)
		return (FAILURE);
	mlx_info->win = mlx_new_window(mlx_info->mlx, \
	WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (!mlx_info->win)
		return (FAILURE);
	mlx_info->img = mlx_new_image(mlx_info->mlx, \
	WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx_info->img)
		return (FAILURE);
	mlx_info->addr = mlx_get_data_addr(mlx_info->img, \
	&mlx_info->bits_per_pixel, &mlx_info->line_length, &mlx_info->endian);
	return (SUCCESS);
}

// 順番不明のため、scene, cameraを同時に初期化する
static int	init_scene_and_camera(t_all_info *all_info, const char *rt_path)
{
	if (parsing_config(all_info, rt_path) == FAILURE)
		return (FAILURE);
	if (validate_scene(all_info->scene_info) == FAILURE)
		return (FAILURE);
	if (validate_camera(all_info->camera_info) == FAILURE)
		return (FAILURE);
	debug_print_config(all_info);
	update_scene(all_info->scene_info); // color = brightness * color,...
	return (SUCCESS);
}

int	construct_info(t_all_info *all_info, const char *rt_path)
{
	if (alloc_info_ptr(all_info) == FAILURE)
		return (FAILURE);
	if (init_mlx(all_info->mlx_info) == FAILURE)
		return (FAILURE);
	if (init_scene_and_camera(all_info, rt_path) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
