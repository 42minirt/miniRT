/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:55:01 by user              #+#    #+#             */
/*   Updated: 2023/05/17 23:28:59 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//intersectionが存在するかとともに、存在していればintersectionの情報を格納する

static double	calc_intersection(t_obj *obj, t_ray eye2screen, t_intersection_point *tmp_itsp)
{
	if (obj->type == BALL)
		return (calc_intersect_with_sphere(obj, eye2screen, tmp_itsp));
	else if (obj->type == PLANE)
		return (calc_planeratio(obj, &eye2screen, tmp_itsp));
	else if (obj->type == CYLINDER)
		return (calc_cylinderratio(obj, &eye2screen, tmp_itsp));
	return (calc_intersect_with_corn(obj, eye2screen, tmp_itsp));
}

bool	check_intersection(t_scene_info *scene, t_ray eye2screen, t_intersection_point *its_p)
{
	double					t;
	double					tmp_t;
	t_list					*obj_node;
	t_intersection_point	*tmp_itsp;

	t = INFINITY;
	its_p = NULL;
	tmp_itsp = NULL;
	obj_node = scene->objs;
	//intersectionが存在しているか確認
	while (obj_node != NULL)
	{
		tmp_t = calc_intersection(obj_node->content, eye2screen, tmp_itsp);
		if (tmp_t >= 0 && tmp_t < t)
		{
			t = tmp_t;
			its_p = tmp_itsp;
		}
		obj_node = obj_node->next;
	}
	if (its_p == NULL)
		return (false);
	else
		return (true);
}

static bool	recursive_raytrace(t_all_info *info, t_ray eye2screen, \
									t_color *ret_color, size_t counter)
{
	bool					is_intersect;
	t_color					color;
	t_intersection_point	its_p;

	counter++;	// tmp
	if (counter > MAX_RECURSION)
		return (false);

	// 交点判定
	is_intersect = check_intersection(info->scene_info, eye2screen, &its_p);
    if (is_intersect == false)
        return (false);

	// 色の計算（background or obj color
	color_set(&color, 0.0, 0.0, 0.0);
	color = color_add(color, calc_ambient_reflection(info->scene_info));
	color = color_add(color, calc_diffuse_reflection(info->scene_info, &its_p, eye2screen));
//	color = color_add(color, calc_specular_reflection(info, &its_p, eye2screen));
//	color = color_add(color, calc_perfect_reflection(info, &its_p, eye2screen));
	*ret_color = color;
    return (true);
}

bool	raytrace(t_all_info *info, t_ray eye2screen, t_color *color)
{
	return (recursive_raytrace(info, eye2screen, color, 0));
}
