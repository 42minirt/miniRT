/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:55:01 by user              #+#    #+#             */
/*   Updated: 2023/06/14 01:55:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "minirt.h"
#include "raytrace.h"

static double	calc_intersection(t_obj *obj, \
									t_ray eye2screen, \
									t_intersection_point *tmp_itsp)
{
	if (streq(obj->id_str, ID_SPHERE))
		return (calc_intersect_with_sphere(obj, eye2screen, tmp_itsp));
	else if (streq(obj->id_str, ID_PLANE))
		return (calc_planeratio(obj, &eye2screen, tmp_itsp));
	else if (streq(obj->id_str, ID_CYLINDER))
		return (calc_cylinderratio(obj, &eye2screen, tmp_itsp));
	else if (streq(obj->id_str, ID_CORN))
		return (calc_intersect_with_corn(obj, eye2screen, tmp_itsp));
	return (-1.0);
}

bool	check_intersection(t_scene_info *scene, \
							t_ray eye2screen, \
							t_intersection_point *its_p)
{
	double					ret_t;
	double					tmp_t;
	t_list					*obj_node;
	t_intersection_point	tmp_itsp;
	t_intersection_point	nearest_itsp;

	ret_t = INFINITY;
	obj_node = scene->objs;
	while (obj_node != NULL)
	{
		tmp_t = calc_intersection(obj_node->content, eye2screen, &tmp_itsp);
		if (0.0 < tmp_t && tmp_t < ret_t)
		{
			ret_t = tmp_t;
			nearest_itsp = tmp_itsp;
		}
		obj_node = obj_node->next;
	}
	if (isinf(ret_t))
		return (false);
	*its_p = nearest_itsp;
	return (true);
}

t_color	recursive_raytrace(t_all_info *info, \
							t_ray eye2screen, \
							size_t counter)
{
	t_color					color;
	t_intersection_point	its_pos;

	counter++;
	if (counter > MAX_RECURSION)
		return (init_color_hex(0x000000));
	if (!check_intersection(info->scene_info, eye2screen, &its_pos))
		return (init_color_hex(0x000000));
	its_pos.normal = get_pl_sp_drawable_normal(its_pos, eye2screen.unit_dir);
	color = calc_ambient_reflection(info->scene_info, its_pos);
	color = color_add(color, \
		calc_diffuse_reflection(info->scene_info, its_pos, eye2screen));
	color = color_add(color, \
		calc_specular_reflection(info, &its_pos, eye2screen));
	color = color_add(color, \
		calc_perfect_reflection(info, &its_pos, eye2screen, counter));
	return (color);
}

t_color	raytrace(t_all_info *info, t_ray eye2screen)
{
	return (recursive_raytrace(info, eye2screen, 0));
}
