/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:55:01 by user              #+#    #+#             */
/*   Updated: 2023/05/24 22:24:38 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//intersectionが存在するかとともに、存在していればintersectionの情報を格納する

static double	calc_intersection(t_obj *obj, t_ray eye2screen, t_intersection_point *tmp_itsp)
{
	if (is_equal_strings(obj->id_str, ID_SPHERE))
		return (calc_intersect_with_sphere(obj, eye2screen, tmp_itsp));
	else if (is_equal_strings(obj->id_str, ID_PLANE))
		return (calc_planeratio(obj, &eye2screen, tmp_itsp));
	else if (is_equal_strings(obj->id_str, ID_CYLINDER))
		return (calc_cylinderratio(obj, &eye2screen, tmp_itsp));
	else if (is_equal_strings(obj->id_str, ID_CORN))
		return (calc_intersect_with_corn(obj, eye2screen, tmp_itsp));
	return (-1.0);
}

bool	check_intersection(t_scene_info *scene, t_ray eye2screen, t_intersection_point *its_p)
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
		if (0 < tmp_t && tmp_t < ret_t)
		{
			ret_t = tmp_t;
			nearest_itsp = tmp_itsp;
		}
		obj_node = obj_node->next;
	}
	if (ret_t == INFINITY)
		return (false);
	*its_p = nearest_itsp;
	return (true);
}

t_color	recursive_raytrace(t_all_info *info, t_ray eye2screen, \
									size_t counter)
{
	bool					is_intersect;
	t_color					ret_color;
	t_intersection_point	its_p;

	counter++;	// tmp
	color_set(&ret_color, 0.0, 0.0, 0.0);
	if (counter > MAX_RECURSION)
		return (ret_color);

	// 交点判定
	is_intersect = check_intersection(info->scene_info, eye2screen, &its_p);
    if (is_intersect == false)
// <<<<<<< HEAD
	{
        return (ret_color);
	}
	ret_color = color_add(ret_color, calc_diffuse_reflection(info->scene_info, its_p, eye2screen));
	ret_color = color_add(ret_color, calc_specular_reflection(info, &its_p, eye2screen));
	if (its_p.obj->obj_color.is_perfect_ref == true)
		ret_color = color_add(ret_color, calc_perfect_reflection(info, &its_p, eye2screen, counter));
	return (ret_color);
// =======
// 		return (false);

// 	// 色の計算（background or obj color
// 	color_set(&color, 0.0, 0.0, 0.0);
// //	color_set(&color, 1, 0.0, 0.0);
// 	color = color_add(color, calc_ambient_reflection(info->scene_info, its_p));
// 	color = color_add(color, calc_diffuse_reflection(info->scene_info, its_p, eye2screen));
// //	color = color_add(color, calc_specular_reflection(info, &its_p, eye2screen));
// //	color = color_add(color, calc_perfect_reflection(info, &its_p, eye2screen));
// 	*ret_color = color;
//     return (true);
// >>>>>>> origin/takira
}

t_color	raytrace(t_all_info *info, t_ray eye2screen)
{
	return (recursive_raytrace(info, eye2screen, 0));
}
