#include "minirt.h"

//static void	free_objs(void *content)
//{
//	t_obj		*obj;
//
//	obj = content;
//	if (obj)
//	{
//		free(obj->obj_color->texture_data);
//		free(obj->obj_color->bump_data);
//	}
//	free(obj);
//}

static void	free_scene(t_scene_info *scene)
{
	ft_lstclear(&scene->lights, free);
//	ft_lstclear(&scene->lights, free_objs);
	ft_lstclear(&scene->objs, free);
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