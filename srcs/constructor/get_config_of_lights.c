/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_of_lights.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// #Light      point(xyz)         ratio[0,1]                  RGB[0,255]
// #Spotlight  Light_point(xyz)   ratio[0,1]   angle[0-180]   RGB[0,255]
static t_parse_res	get_pointlight_detail(const char *line, t_light *light)
{
	size_t		idx;
	t_parse_res	res;

	idx = 0;
	res = parse_vec(line, &light->point, &idx);
	if (res != PASS)
		return (res);
	res = parse_double(line, &light->brightness, &idx);
	if (res != PASS)
		return (res);
	res = parse_color(line, &light->light_color, &idx);
	if (res != PASS)
		return (res);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}

static t_parse_res	get_spotlight_detail(const char *line, t_light *light)
{
	size_t		idx;
	t_parse_res	res;

	idx = 0;
	res = parse_vec(line, &light->point, &idx);
	if (res != PASS)
		return (res);
	res = parse_vec(line, &light->sl_dir, &idx);
	if (res != PASS)
		return (res);
	res = parse_double(line, &light->brightness, &idx);
	if (res != PASS)
		return (res);
	res = parse_double(line, &light->sl_angle, &idx);
	if (res != PASS)
		return (res);
	res = parse_color(line, &light->light_color, &idx);
	if (res != PASS)
		return (res);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}

static t_parse_res	get_light_detail(const char *line, t_light *light)
{
	t_parse_res	parse_result;

	if (is_equal_strings(light->id_type, ID_LIGHT))
		parse_result = get_pointlight_detail(line, light);
	else
		parse_result = get_spotlight_detail(line, light);
	return (parse_result);
}

static t_light	*init_light_ptr(const char *id_str)
{
	t_light	*light;

	light = (t_light *)ft_calloc(sizeof(t_light), 1);
	if (!light)
		return (NULL);
	light->id_type = id_str;
	return (light);
}

t_parse_res	get_config_of_lights(const char *line, \
								t_scene_info *scene, const char *id_str)
{
	t_list			*new_list;
	t_light			*light;
	t_parse_res		parse_result;

	light = init_light_ptr(id_str);
	if (!light)
		return (ERROR_FATAL);
	parse_result = get_light_detail(line, light);
	if (parse_result != PASS)
	{
		x_free_1d_alloc((void **)&light);
		return (parse_result);
	}
	new_list = ft_lstnew(light);
	if (!new_list)
	{
		x_free_1d_alloc((void **)&light);
		return (ERROR_FATAL);
	}
	ft_lstadd_back(&scene->lights, new_list);
	return (PASS);
}
