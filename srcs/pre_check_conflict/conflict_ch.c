/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conflict_ch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:56:45 by user              #+#    #+#             */
/*   Updated: 2023/06/14 21:35:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	conflict_ch_sameobj(t_obj *obj, t_light	*light_info)
{
	if (is_equal_strings(obj->id_str, ID_SPHERE))
		return (ch_conflict_spere(obj->shape_data.sphere, light_info));
	else if (is_equal_strings(obj->id_str, ID_PLANE))
		return (ch_conflict_plane(obj->shape_data.plane, light_info));
	else if (is_equal_strings(obj->id_str, ID_CYLINDER))
		return (ch_conflict_cylinder(obj->shape_data.cylinder, light_info));
	return (ch_conflict_corn(obj->shape_data.corn, light_info));
}

//objのリスト分だけwhileを回す
//その中で各種objと光源の距離を測り、距離がイプシロン以下かどうかを判定していく
//光源の数　objの数　といった形でwhileを組む
//光源の数
//	objの数

bool	conflict_ch(t_all_info *info)
{
	t_list	*lgt_list;
	t_list	*obj_list;

	lgt_list = info->scene_info->lights;
	obj_list = info->scene_info->objs;
	while (lgt_list)
	{
		while (obj_list)
		{
			if (conflict_ch_sameobj(obj_list->content, \
			lgt_list->content) == true)
				return (true);
			obj_list = obj_list->next;
		}
		lgt_list = lgt_list->next;
		obj_list = info->scene_info->objs;
	}
	return (false);
}
