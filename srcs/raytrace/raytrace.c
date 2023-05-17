/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:55:01 by user              #+#    #+#             */
/*   Updated: 2023/05/17 22:21:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

//色の計算はambient_reflection　diffuse_reflection　specular_reflection　perfect_reflection　で行う
t_color	calc_color(t_scene_info *scene_info, t_ray eye2screen)
{

}

//intersectionが存在するかとともに、存在していればintersectionの情報を格納する


static double	calc_intersection(t_list *obj, t_all_info info, t_ray eye2screen, t_intersection_point *tmp_itsp)
{
	t_obj	*shape;

	shape = (t_obj *)obj->content;
	if (shape->type == BALL)
		return (calc_ratio_ball(shape, info, eye2screen, tmp_itsp));
	else if (shape->type == PLANE)
		return (calc_ratio_plane(shape, info, eye2screen, tmp_itsp));
	else if (shape->type == CYLINDER)
		return (calc_ratio_cylinder(shape, info, eye2screen, tmp_itsp));
	return (calc_ratio_cylinder(shape, info, eye2screen, tmp_itsp));
}

static bool	check_intersection(t_all_info info, t_ray eye2screen, t_intersection_point *its_p)
{
	double					t;
	double					tmp_t;
	t_list					*obj;
	t_intersection_point	*tmp_itsp;

	t = INFINITY;
	its_p = NULL;
	tmp_itsp = NULL;
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

t_color raytrace(t_all_info info, t_ray eye2screen)
{
	bool					is_intersect;
	t_color					color;
	t_intersection_point	its_p;

	// 交点判定
	is_intersect = check_intersection(info, eye2screen, &its_p);
    if (is_intersect == false)
        return (backgroundcolor_init());
	// 色の計算（background or obj color
	
	color = calc_color(info.scene_info, eye2screen);
    return (color);
}

///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   raytrace.c                                         :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2023/05/14 21:55:01 by user              #+#    #+#             */
///*   Updated: 2023/05/14 23:28:18 by user             ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "includes/minirt.h"
//
////色の計算はambient_reflection　diffuse_reflection　specular_reflection　perfect_reflection　で行う
//t_color	calc_color(t_scene_info *scene_info, t_ray eye2screen)
//{
//
//}
//
////intersectionが存在するかとともに、存在していればintersectionの情報を格納する
//
//
//static double	calc_intersection(t_list *obj, t_all_info info, t_ray eye2screen, t_intersection_point *tmp_itsp)
//{
//	t_obj	*shape;
//
//	shape = (t_obj *)obj->content;
//	if (shape->type == BALL)
//		return (calc_ratio_ball(shape, info, eye2screen, tmp_itsp));
//	else if (shape->type == PLANE)
//		return (calc_ratio_plane(shape, info, eye2screen, tmp_itsp));
//	else if (shape->type == CYLINDER)
//		return (calc_ratio_cylinder(shape, info, eye2screen, tmp_itsp));
//	return (calc_ratio_cylinder(shape, info, eye2screen, tmp_itsp));
//}
//
//bool	check_intersection(t_all_info info, t_ray eye2screen, t_intersection_point *its_p)
//{
//	double	t;
//	double	tmp_t;
//	t_list	*obj;
//	t_intersection_point	*tmp_itsp;
//
//	t = INFINITY;
//	its_p = NULL;
//	tmp_itsp = NULL;
//	//intersectionが存在しているか確認
//	while (obj != NULL)
//	{
//		tmp_t = calc_intersection(obj, info, eye2screen, tmp_itsp);
//		if (tmp_t >= 0 && tmp_t < t)
//		{
//			t = tmp_t;
//			its_p = tmp_itsp;
//		}
//		obj = obj->next;
//	}
//	if (its_p == NULL)
//		return (false);
//	else
//		return (true);
//}
//
//t_color raytrace(t_all_info info, t_ray eye2screen)
//{
//	bool					is_intersect;
//	t_color					color;
//	t_intersection_point	its_p;
//
//	// 交点判定
//	is_intersect = check_intersection(info, eye2screen, &its_p);
//    if (is_intersect == false)
//        return (backgroundcolor_init());
//	// 色の計算（background or obj color
//    init_color(&color);
//
//	color = calc_color(info.scene_info, eye2screen);
//    return (color);
//}
