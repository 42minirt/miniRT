#include "minirt.h"

static void	initialize_by_zero(t_all_info *all_info)
{
	all_info->mlx_info->mlx = NULL;
	all_info->mlx_info->win = NULL;
	all_info->mlx_info->img = NULL;
	all_info->mlx_info->addr = NULL;

	all_info->scene_info->lights = NULL;
	all_info->scene_info->objs = NULL;

	all_info->scene_info->brightness = -1.0;

	all_info->camera_info = NULL;	//todo
}

static int	init_mlx(t_mlx_info *mlx_info)
{
	if (!mlx_info->mlx)
		return (FAILURE);
	mlx_info->win = mlx_new_window(mlx_info->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (!mlx_info->win)
		return (FAILURE);
	mlx_info->img = mlx_new_image(mlx_info->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx_info->img)
		return (FAILURE);

	mlx_info->addr = mlx_get_data_addr(mlx_info->img, &mlx_info->bits_per_pixel, &mlx_info->line_length, &mlx_info->endian);
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
	return (SUCCESS);
}

int	construct_info(t_all_info *all_info, const char *rt_path)
{
	initialize_by_zero(all_info);
	if (init_mlx(all_info->mlx_info) == FAILURE)
		return (FAILURE);

	if (init_scene_and_camera(all_info, rt_path) == FAILURE)
		return (FAILURE);

	update_scene(all_info->scene_info); // color = brightness * color,...
	return (SUCCESS);
}
