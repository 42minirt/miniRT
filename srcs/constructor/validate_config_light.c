/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config_light.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:37:11 by user              #+#    #+#             */
/*   Updated: 2023/05/20 20:37:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parse_res	validate_ambient_info(t_scene_info *scene)
{
	if (!is_ratio_in_range(scene->brightness))
	{
		printf("   [DEBUG] ambient NG :: brightness out of range\n");
		return (ERROR_OUT_OF_RANGE);
	}
	if (!is_color_in_range(scene->ambient_color))
	{
		printf("   [DEBUG] ambient NG :: color out of range\n");
		return (ERROR_OUT_OF_RANGE);
	}
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
		if (light->type == LT_POINT)
		{
			if (!is_angle_in_range(light->sl_angle))
				return (ERROR_OUT_OF_RANGE);
		}
		node = node->next;
	}
	return (PASS);
}
