/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_camera_and_light_overlap_with_obj.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:56:45 by user              #+#    #+#             */
/*   Updated: 2023/06/14 21:35:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static bool	conflict_ch_sameobj(t_obj *obj, t_vec check_pos)
{
	if (is_equal_strings(obj->id_str, ID_SPHERE))
		return (ch_conflict_spere(obj->shape_data.sphere, check_pos));
	else if (is_equal_strings(obj->id_str, ID_PLANE))
		return (ch_conflict_plane(obj->shape_data.plane, check_pos));
	else if (is_equal_strings(obj->id_str, ID_CYLINDER))
		return (ch_conflict_cylinder(obj->shape_data.cylinder, check_pos));
	return (ch_conflict_corn(obj->shape_data.corn, check_pos));
}

//objのリスト分だけwhileを回す
//その中で各種objと光源の距離を測り、距離がイプシロン以下かどうかを判定していく
//光源の数　objの数　といった形でwhileを組む
//光源の数
//	objの数

static bool	is_light_overlap(t_obj *obj, t_list *light_node)
{
	t_list	*node;
	t_light	*light;

	node = light_node;
	while (node)
	{
		light = node->content;
		if (conflict_ch_sameobj(obj, light->point))
			return (true);
		node = node->next;
	}
	return (false);
}

static bool	is_camera_overlap(t_obj *obj, t_camera_info *camera)
{
	return (conflict_ch_sameobj(obj, camera->position));
}

bool	is_camera_and_light_overlap_with_obj(t_all_info *info)
{
	t_list	*obj_node;

	obj_node = info->scene_info->objs;
	while (obj_node)
	{
		if (is_camera_overlap(obj_node->content, info->camera_info))
		{
			ft_dprintf(STDERR_FILENO, "%s\n : %s\n", MSG_ERROR, MSG_CAMERA_OVERLAP);
			return (true);
		}
		if (is_light_overlap(obj_node->content, info->scene_info->lights))
		{
			ft_dprintf(STDERR_FILENO, "%s\n : %s\n", MSG_ERROR, MSG_LIGHT_OVERLAP);
			return (true);
		}
		obj_node = obj_node->next;
	}
	return (false);
}
