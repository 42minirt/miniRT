/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_parse_res	validate_objects_info(t_scene_info *scene)
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
	if (!is_vec_in_normal_range(camera->direction))
		return (ERROR_OUT_OF_RANGE);
	if (!is_fov_in_range(camera->fov_deg))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}
