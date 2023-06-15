/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/06/14 21:38:28 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	alloc_info_ptr(t_all_info *all_info)
{
	all_info->mlx_info = NULL;
	all_info->scene_info = NULL;
	all_info->camera_info = NULL;
	all_info->mlx_info = (t_mlx_info *)ft_calloc(1, sizeof(t_mlx_info));
	if (!all_info->mlx_info)
		return (FAILURE);
	all_info->scene_info = (t_scene_info *)ft_calloc(1, sizeof(t_scene_info));
	if (!all_info->scene_info)
		return (FAILURE);
	all_info->scene_info->lights = NULL;
	all_info->scene_info->objs = NULL;
	all_info->camera_info = \
		(t_camera_info *)ft_calloc(1, sizeof(t_camera_info));
	if (!all_info->camera_info)
		return (FAILURE);
	return (SUCCESS);
}

static int	init_mlx(t_mlx_info *mlx_info)
{
	mlx_info->mlx = mlx_init();
	if (!mlx_info->mlx)
		return (FAILURE);
	mlx_info->win = mlx_new_window(mlx_info->mlx, \
									WINDOW_WIDTH, WINDOW_HEIGHT, \
									WINDOW_TITLE);
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

// parse scene & camera -> update config
static t_parse_res	init_scene_and_camera(t_all_info *all_info, \
											const char *rt_path)
{
	t_parse_res	result;

	result = parsing_config(all_info, rt_path);
	if (result != PASS)
		return (result);
	result = validate_scene(all_info->scene_info);
	if (result != PASS)
		return (result);
	result = validate_camera(all_info->camera_info);
	if (result != PASS)
		return (result);
	update_scene_config(all_info->scene_info);
	update_camera_config(all_info->camera_info);
	return (result);
}
// debug_print_config(all_info);

static int	put_err_ret_failure(char *err)
{
	ft_dprintf(STDERR_FILENO, "%s\n : %s\n", MSG_ERROR, err);
	return (FAILURE);
}

int	construct_info(t_all_info *all_info, const char *rt_path)
{
	t_parse_res	result;

	if (alloc_info_ptr(all_info) == FAILURE)
		return (put_err_ret_failure(MSG_ERR_NOMEM));
	if (init_mlx(all_info->mlx_info) == FAILURE)
		return (put_err_ret_failure(MSG_ERR_MLX));
	result = init_scene_and_camera(all_info, rt_path);
	if (result != PASS)
	{
		ft_dprintf(STDERR_FILENO, \
		"%s\n : %s [%s]\n", \
		MSG_ERROR, MSG_ERR_CONFIG, get_parse_result_char(result));
		return (FAILURE);
	}
	printf("[Load %s] : %s\n", rt_path, get_parse_result_char(result));
	return (SUCCESS);
}
