/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config_light.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_parse_res	validate_ambient_info(t_scene_info *scene)
{
	if (!is_ratio_in_range(scene->brightness))
		return (ERROR_OUT_OF_RANGE);
	if (!is_color_in_range(scene->ambient_color))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_pointlight(t_light *light)
{
	if (!is_ratio_in_range(light->brightness))
		return (ERROR_OUT_OF_RANGE);
	if (!is_color_in_range(light->light_color))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_spotlight(t_light *light)
{
	if (!is_normal_vec_in_range(light->sl_dir))
		return (ERROR_OUT_OF_RANGE);
	if (!is_ratio_in_range(light->brightness))
		return (ERROR_OUT_OF_RANGE);
	if (!is_angle_in_range(light->sl_angle))
		return (ERROR_OUT_OF_RANGE);
	if (!is_color_in_range(light->light_color))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_lights(t_light *light)
{
	t_parse_res	res;

	if (is_equal_strings(light->id_type, ID_LIGHT))
		res = validate_pointlight(light);
	else
		res = validate_spotlight(light);
	return (res);
}

t_parse_res	validate_lights_info(t_scene_info *scene)
{
	t_list		*node;
	t_parse_res	res;

	node = scene->lights;
	while (node)
	{
		res = validate_lights(node->content);
		if (res != PASS)
			return (res);
		node = node->next;
	}
	return (PASS);
}
