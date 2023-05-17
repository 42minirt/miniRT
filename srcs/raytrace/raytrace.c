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

static double	calc_intersection(t_list *obj, t_all_info *info, t_ray eye2screen, t_intersection_point *tmp_itsp)
{
	t_obj	*shape;

	shape = (t_obj *)obj->content;
	if (shape->type == BALL)
		return (calc_intersect_with_sphere(shape, eye2screen, tmp_itsp));
	else if (shape->type == PLANE)
		return (calc_planeratio(shape, info, &eye2screen, tmp_itsp));
	else if (shape->type == CYLINDER)
		return (calc_cylinderratio(shape, info, &eye2screen, tmp_itsp));
	return (calc_intersect_with_corn(shape, eye2screen, tmp_itsp));
}

static bool	check_intersection(t_all_info *info, t_ray eye2screen, t_intersection_point *its_p)
{
	double					t;
	double					tmp_t;
	t_list					*obj;
	t_intersection_point	*tmp_itsp;

	t = INFINITY;
	its_p = NULL;
	tmp_itsp = NULL;
	obj = info->scene_info->objs;
	//intersectionが存在しているか確認
	while (obj != NULL)
	{
		tmp_t = calc_intersection(obj, info, eye2screen, tmp_itsp);
		if (tmp_t >= 0 && tmp_t < t)
		{
			t = tmp_t;
			its_p = tmp_itsp;
		}
		obj = obj->next;
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

	if (counter > MAX_RECURSION)
		return (false);
	// 交点判定
	is_intersect = check_intersection(info, eye2screen, &its_p);
    if (is_intersect == false)
        return (false);

	// 色の計算（background or obj color
	color_set(&color, 0.0, 0.0, 0.0);
	color = color_add(color, calc_ambient_reflection(info->scene_info));
	color = color_add(color, calc_diffuse_reflection(info, &its_p, eye2screen));
	color = color_add(color, calc_specular_reflection(info, &its_p, eye2screen));
	color = color_add(color, calc_perfect_reflection(info, &its_p, eye2screen));
	*ret_color = color;
    return (true);
}

bool	raytrace(t_all_info *info, t_ray eye2screen, t_color *color)
{
	return (recursive_raytrace(info, eye2screen, color, 0));
}
