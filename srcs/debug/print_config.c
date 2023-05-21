/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_lights(t_scene_info *scene)
{
	t_list	*node;
	t_light	*light;
	t_vec	v;
	t_color	c;

	node = scene->lights;
	while (node)
	{
		light = node->content;
		v = light->point;
		c = light->light_color;
		if (is_equal_strings(light->id_type, ID_SPOTLIGHT))
			printf("  Point Light : (%5.1f, %5.1f, %5.1f), " \
			"                                   %5.1f," \
			"           (%5.1f, %5.1f, %5.1f)\n", \
			v.x, v.y, v.z, light->brightness, c.r, c.g, c.b);
		else
			printf("  Spot Light  : (%5.1f, %5.1f, %5.1f), " \
			"                                   %5.1f,   %5.1f," \
			"           (%5.1f, %5.1f, %5.1f)\n", \
			v.x, v.y, v.z, light->brightness, light->sl_angle, c.r, c.g, c.b);
		node = node->next;
	}
}

static void	print_objects(t_scene_info *scene)
{
	t_list	*node;
	t_obj	*obj;

	node = scene->objs;
	while (node)
	{
		obj = node->content;
		if (is_equal_strings(obj->id_str, ID_SPHERE))
			print_sphere(obj);
		else if (is_equal_strings(obj->id_str, ID_PLANE))
			print_plane(obj);
		else if (is_equal_strings(obj->id_str, ID_CYLINDER))
			print_cylinder(obj);
		else
			print_corn(obj);
		node = node->next;
	}
}

void	debug_print_config(t_all_info *info)
{
	t_color	c;

	printf("======================================== "\
	"[DEBUG PRINT CONFIG] ========================================\n");
	c = info->scene_info->ambient_color;
	printf("Ambient       : %5.1f, "\
	"                                  "\
	"                                  (%5.1f, %5.1f, %5.1f)\n", \
	info->scene_info->brightness, c.r, c.g, c.b);
	printf("Camera        : \n");
	printf("Lights\n");
	print_lights(info->scene_info);
	printf("Objects\n");
	print_objects(info->scene_info);
	printf("=================================================="\
	"====================================================\n");
}

const char	*get_parse_result_char(t_parse_res res)
{
	if (res == PASS)
		return ("\x1b[32mPASS\x1b[0m");
	if (res == ERROR_FATAL)
		return ("\x1b[31mERROR_FATAL\x1b[0m");
	if (res == ERROR_INVALID_TYPE)
		return ("\x1b[31mERROR_INVALID_TYPE\x1b[0m");
	if (res == ERROR_LACK_INFO)
		return ("\x1b[31mERROR_LACK_INFO\x1b[0m");
	if (res == ERROR_TOO_MANY_INFO)
		return ("\x1b[31mERROR_TOO_MANY_INFO\x1b[0m");
	if (res == ERROR_INVALID_ARG)
		return ("\x1b[31mERROR_INVALID_ARG\x1b[0m");
	if (res == ERROR_OUT_OF_RANGE)
		return ("\x1b[31mERROR_OUT_OF_RANGE\x1b[0m");
	if (res == ERROR_MULTIPLE_ID)
		return ("\x1b[31mERROR_MULTIPLE_ID\x1b[0m");
	if (res == ERROR_MISSING_ID)
		return ("\x1b[31mERROR_MISSING_ID\x1b[0m");
	if (res == ERROR_INVALID_PPM_FORMAT)
		return ("\x1b[31mERROR_INVALID_PPM_FORMAT\x1b[0m");
	return ("\x1b[31mERROR\x1b[0m");
}
