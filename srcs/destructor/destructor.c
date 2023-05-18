/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_objs(void *content)
{
	t_obj		*obj;

	obj = content;
	if (obj)
	{
		free(obj->obj_color.texture_data.data);
		free(obj->obj_color.bump_data.data);
	}
	free(obj);
}

static void	free_scene(t_scene_info *scene)
{
	ft_lstclear(&scene->lights, free);
	ft_lstclear(&scene->objs, free_objs);
	free(scene);
}

static void	free_mlx(t_mlx_info *mlx)
{
	if (!mlx)
		return ;
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx);
}

void	destruct_info(t_all_info *info)
{
	free_mlx(info->mlx_info);
	free_scene(info->scene_info);
	free(info->camera_info);
}
