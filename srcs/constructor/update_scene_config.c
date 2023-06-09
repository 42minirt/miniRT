/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:45:55 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	update_config_ambient_color(t_scene_info *scene)
{
	scene->ambient_color = \
	color_k1c1(1.0 / 255.0, scene->ambient_color);
}

static void	update_scene_each_obj(t_obj *obj)
{
	if (is_equal_strings(obj->id_str, ID_SPHERE))
		update_scene_sphere_info(&obj->shape_data.sphere);
	else if (is_equal_strings(obj->id_str, ID_PLANE))
		update_scene_plane_info(&obj->shape_data.plane);
	else if (is_equal_strings(obj->id_str, ID_CYLINDER))
		update_scene_cylinder_info(&obj->shape_data.cylinder);
	else if (is_equal_strings(obj->id_str, ID_CORN))
		update_scene_corn_info(&obj->shape_data.corn);
}

static void	update_config_objs(t_scene_info *scene)
{
	t_list	*node;
	t_obj	*obj;

	node = scene->objs;
	while (node)
	{
		obj = node->content;
		obj->obj_color.ka = color_k1c1(1.0 / 255.0, obj->obj_color.ka);
		obj->obj_color.kd = color_k1c1(1.0 / 255.0, obj->obj_color.kd);
		obj->obj_color.ks = color_k1c1(1.0 / 255.0, obj->obj_color.ks);
		obj->obj_color.kf = color_k1c1(1.0 / 255.0, obj->obj_color.kf);
		if (obj->obj_color.is_checker)
			obj->obj_color.checker_color = \
			color_k1c1(1.0 / 255.0, obj->obj_color.checker_color);
		update_scene_each_obj(obj);
		node = node->next;
	}
}

void	update_scene_config(t_scene_info *scene)
{
	update_config_ambient_color(scene);
	update_config_lights(scene);
	update_config_objs(scene);
}
