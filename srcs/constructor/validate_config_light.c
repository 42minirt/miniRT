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

t_parse_res	validate_lights_info(t_scene_info *scene)
{
	t_list	*node;
	t_light	*light;

	node = scene->lights;
	while (node)
	{
		light = node->content;
		if (!is_ratio_in_range(light->brightness))
			return (ERROR_OUT_OF_RANGE);
		if (!is_color_in_range(light->light_color))
			return (ERROR_OUT_OF_RANGE);
		if (is_equal_strings(light->id_type, ID_SPOTLIGHT) \
		&& !is_angle_in_range(light->sl_angle))
			return (ERROR_OUT_OF_RANGE);
		node = node->next;
	}
	return (PASS);
}
