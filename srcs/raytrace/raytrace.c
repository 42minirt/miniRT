/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:55:01 by user              #+#    #+#             */
/*   Updated: 2023/05/20 20:38:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//色の計算はambient_reflection　diffuse_reflection　specular_reflection　perfect_reflection　で行う
t_color	calc_color(t_scene_info *scene_info, t_ray eye2screen)
{

}

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

t_color	recursive_raytrace(t_all_info *info, t_ray eye2screen, size_t counter)
{
	bool					is_intersect;
	t_color					color;
	t_intersection_point	its_p;

	color_set(&color, 0.0, 0.0, 0.0);
	if (counter > MAX_RECURSION)
		return (color);
	// 交点判定
	is_intersect = check_intersection(info, eye2screen, &its_p);
    if (is_intersect == false)
        return (backgroundcolor_init());
	color = color_add(color, calc_diffuse_reflection(info, its_p, eye2screen));
	color = color_add(color, calc_specular_reflection(info, its_p, eye2screen));
	if (its_p.obj->obj_color.is_perfect_ref == true)
		color = color_add(color, calc_perfect_reflection(info, its_p, eye2screen, counter));
    return (color);
}

t_color raytrace(t_all_info *info, t_ray eye2screen)
{
	return (recursive_raytrace(info, eye2screen, 0));
}
