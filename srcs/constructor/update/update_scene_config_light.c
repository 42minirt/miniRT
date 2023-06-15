/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene_config_light.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constructor.h"
#include "color.h"
#include "typedef.h"
#include "vector.h"

static void	update_config_pointlight(t_light *light)
{
	light->light_color = \
		color_k1c1(light->brightness / 255.0, light->light_color);
}

static void	update_config_spotlight(t_light *light)
{
	light->sl_direction = norm_vec(light->sl_direction);
	light->sl_angle_half = light->sl_angle / 2.0;
	light->light_color = \
		color_k1c1(light->brightness / 255.0, light->light_color);
}

void	update_config_lights(t_scene_info *scene)
{
	t_list	*node;
	t_light	*light;

	node = scene->lights;
	while (node)
	{
		light = node->content;
		if (streq(light->id_type, ID_LIGHT))
			update_config_pointlight(light);
		else
			update_config_spotlight(light);
		node = node->next;
	}
}
