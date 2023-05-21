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

#include "../../includes/minirt.h"

void	free_objs(void *content)
{
	t_obj	*obj;

	obj = content;
	if (obj)
	{
		x_free_1d_alloc((void **)&obj->obj_color.texture_data.data);
		x_free_1d_alloc((void **)&obj->obj_color.bump_data.data);
		x_free_1d_alloc((void **)&obj->id_str);
	}
	x_free_1d_alloc((void **)&obj);
}

void	free_lights(void *content)
{
	t_light	*light;

	light = content;
	if (light)
	{
		x_free_1d_alloc((void **)&light->id_type);
	}
	x_free_1d_alloc((void **)&light);
}

static void	free_scene(t_scene_info *scene)
{
	ft_lstclear(&scene->lights, free_lights);
	ft_lstclear(&scene->objs, free_objs);
	x_free_1d_alloc((void **)&scene);
}

static void	free_mlx(t_mlx_info *mlx)
{
	if (!mlx)
		return ;
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	x_free_1d_alloc((void **)&mlx->mlx);
	x_free_1d_alloc((void **)&mlx);
}

void	destruct_info(t_all_info *info)
{
	free_mlx(info->mlx_info);
	free_scene(info->scene_info);
	x_free_1d_alloc((void **)&info->camera_info);
}
