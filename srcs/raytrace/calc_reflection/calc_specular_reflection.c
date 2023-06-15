/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_specular_reflection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:31:43 by user              #+#    #+#             */
/*   Updated: 2023/06/14 01:40:59 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "raytrace.h"
#include "vector.h"

static double	calc_v_r(double n_l, \
							t_intersection_point *its_p, \
							t_vec dir_pos2lgt, \
							t_ray *eye2screen)
{
	t_vec	ref_dir;
	t_vec	ref_dir_n;
	t_vec	reverse_eyedir_vec;
	t_vec	reverse_eyedir_vec_n;

	if (n_l <= 0.0)
		return (-1.0);
	ref_dir = vec_k1v1_k2v2(2.0 * n_l, \
	get_bump_normal(its_p), -1.0, dir_pos2lgt);
	normalize(&ref_dir_n, &ref_dir);
	inverse_vec(&reverse_eyedir_vec, &eye2screen->unit_dir);
	normalize(&reverse_eyedir_vec_n, &reverse_eyedir_vec);
	return (dot_vec(&reverse_eyedir_vec_n, &ref_dir_n));
}

static void	calc_spec_col(t_color *color, \
							double v_r, \
							t_light *light_info, \
							t_obj_color obj_color)
{
	double	v_r_alpha;
	t_color	specular_color;

	v_r_alpha = pow(v_r, obj_color.shininess);
	specular_color = color_k1c1k2c2(v_r_alpha, \
									light_info->light_color, \
									1.0, \
									obj_color.ks);
	color_add_pointer(color, color, &specular_color);
}

static bool	is_calc_specular(t_vec *dir_pos2lgt_n, t_light *lgt)
{
	t_vec	unit_lgt2pos;
	bool	ret;

	if (is_equal_strings(lgt->id_type, ID_LIGHT))
		return (true);
	inverse_vec(&unit_lgt2pos, dir_pos2lgt_n);
	unit_lgt2pos = norm_vec(unit_lgt2pos);
	ret = is_in_range_spotlight(unit_lgt2pos, lgt);
	return (ret);
}

static t_color	calc_specref(t_scene_info *scene_info, \
								t_intersection_point *its_p, \
								t_ray eye2screen, \
								t_color color)
{
	t_list	*light;
	t_light	*lgt_info;
	t_vec	dir_pos2lgt;
	t_vec	dir_pos2lgt_n;
	double	v_r;

	light = scene_info->lights;
	while (light != NULL)
	{
		lgt_info = light->content;
		neg_vec(&dir_pos2lgt, &lgt_info->point, &its_p->position);
		if (!is_obj_btw_pos_light(scene_info, its_p->position, dir_pos2lgt))
		{
			dir_pos2lgt_n = norm_vec(dir_pos2lgt);
			if (is_calc_specular(&dir_pos2lgt_n, lgt_info) == true)
			{
				v_r = calc_v_r(calc_dot_n_l(*its_p, eye2screen, dir_pos2lgt_n), \
				its_p, dir_pos2lgt_n, &eye2screen);
				if (v_r > 0.0)
					calc_spec_col(&color, v_r, lgt_info, its_p->obj->obj_color);
			}
		}
		light = light->next;
	}
	return (color);
}

t_color	calc_specular_reflection(t_all_info *info, \
									t_intersection_point *its_p, \
									t_ray eye2screen)
{
	t_color	color;

	color_set(&color, 0.0, 0.0, 0.0);
	if (its_p->obj->obj_color.is_perfect_ref == true)
		return (color);
	return (calc_specref(info->scene_info, its_p, eye2screen, color));
}
