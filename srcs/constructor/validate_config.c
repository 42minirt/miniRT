/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parse_res	validate_objects_info(t_scene_info *scene)
{
	t_list		*node;
	t_obj		*obj;
	t_parse_res	res;

	node = scene->objs;
	while (node)
	{
		obj = node->content;
		res = validate_obj_shape(obj);
		if (res != PASS)
			return (res);
		res = validate_obj_color(obj);
		if (res != PASS)
			return (res);
		node = node->next;
	}
	return (PASS);
}

t_parse_res	validate_scene(t_scene_info *scene)
{
	t_parse_res	res;

	res = validate_ambient_info(scene);
	if (res != PASS)
		return (res);
	res = validate_lights_info(scene);
	if (res != PASS)
		return (res);
	res = validate_objects_info(scene);
	return (res);
}

t_parse_res	validate_camera(t_camera_info *camera)
{
	(void )camera;
	return (PASS);
}
