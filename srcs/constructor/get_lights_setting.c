/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lights_setting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:13:48 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// #Light      point(xyz)         ratio[0,1]                  RGB[0,255]
// #Spotlight  Light_point(xyz)   ratio[0,1]   angle[0-180]   RGB[0,255]
t_parse_res	get_light_detail(const char *line, t_light *light)
{
	size_t	idx;

	idx = 0;
	if (parse_vec(line, &light->point, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parse_double(line, &light->brightness, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_color(line, &light->light_color, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (is_equal_strings(light->id_str, ID_SPOTLIGHT))
		if (parse_double(line, &light->sl_angle, &idx) == FAILURE)
			return (ERROR_INVALID_ARG);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}

static t_light	*init_light(const char *id_str)
{
	t_light	*light;

	light = (t_light *)ft_calloc(sizeof(t_light), 1);
	if (!light)
		return (NULL);
	light->id_str = id_str;
	return (light);
}

t_parse_res	get_lights_setting(const char *line, t_scene_info *scene, const char *id_str)
{
	t_list			*new_list;
	t_light			*light;
	t_parse_res		parse_result;

	light = init_light(id_str);
	if (!light)
		return (ERROR_FATAL);
	parse_result = get_light_detail(line, light);
	if (parse_result != PASS)
	{
		x_free_1d_alloc((void **)&light);
//		free(light);
		return (parse_result);
	}
	new_list = ft_lstnew(light);
	if (!new_list)
	{
		x_free_1d_alloc((void **)&light);
//		free(light);
		return (ERROR_FATAL);
	}
	ft_lstadd_back(&scene->lights, new_list);
	return (PASS);
}
