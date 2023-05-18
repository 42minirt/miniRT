/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_specular_reflection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:31:43 by user              #+#    #+#             */
/*   Updated: 2023/05/18 17:47:34 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

bool	SPOT_check()
{
	return (true);
}

t_color	calc_specref(t_all_info *info, t_intersection_point	its_p, t_ray eye2screen, t_color color)
{
	t_list	*light;
	t_light	*light_info;
	t_vec	dir_pos2lgt;
	t_vec	dir_pos2lgt_n;
	double	n_l;
	t_vec	ref_dir;
	t_vec	ref_dir_n;
	t_vec	reverse_eyedir_vec;
	double	v_r;

	light = info->scene_info->lights;
	while (light != NULL)
	{
		light_info = info->scene_info->lights->content;
		neg_vec(&dir_pos2lgt, &light_info->point, &its_p.position);
		normalize(&dir_pos2lgt_n, &dir_pos2lgt);
		if (light_info->sl_angle == LT_SPOT && SPOT_check() == true)
			continue;
		n_l = dot(its_p.normal, dir_pos2lgt);
		if (n_l <= 0.0)
			return (color);
		ref_dir = vec_k1v1_k2v2(2.0 * n_l, its_p.normal, -1.0, dir_pos2lgt);
		normalize(&ref_dir_n, &ref_dir);
		inverse_vec(&reverse_eyedir_vec, &eye2screen.unit_dir);
		v_r = dot_vec(&reverse_eyedir_vec, &ref_dir);
		//colorの計算
		light = light->next;
	}
}

t_color	calc_specular_reflection(t_all_info *info, t_intersection_point	its_p, t_ray eye2screen)
{
	t_obj	*obj;
	t_color	color;

	color_set(&color, 0.0, 0.0, 0.0);
	if (its_p.obj->type == MT_PERFECT_REFLECTION)
		return (color);
	obj = its_p.obj;
	if (its_p.obj->type == BALL)
		its_p.obj = (t_sphere *)obj;
	else if (its_p.obj->type == PLANE)
		its_p.obj = (t_plane *)obj;
	else if (its_p.obj->type == CORN)
		its_p.obj = (t_corn *)obj;
	else if (its_p.obj->type == CYLINDER)
		its_p.obj = (t_cylinder *)obj;
	return (calc_specref(info, its_p, eye2screen, color));
}