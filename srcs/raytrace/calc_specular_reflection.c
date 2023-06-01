/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_specular_reflection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:31:43 by user              #+#    #+#             */
/*   Updated: 2023/06/01 10:31:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdbool.h>

bool	SPOT_check(t_vec *dir_pos2lgt_n, t_light *lgt_inf)
{
	t_vec	pos2lgt;
	double	alpha;

	inverse_vec(&pos2lgt, dir_pos2lgt_n);
	alpha = acosf(dot_vec(&pos2lgt, &lgt_inf->direction));
	if (alpha > lgt_inf->sl_angle / 2.0f * (double)M_PI / 180.0)
		return (false);
	return (true);
}

double	calc_v_r(double n_l, t_intersection_point *its_p, t_vec dir_pos2lgt, t_ray *eye2screen)
{
	t_vec	ref_dir;
	t_vec	ref_dir_n;
	t_vec	reverse_eyedir_vec;
	t_vec	reverse_eyedir_vec_n;

	if (n_l < 0.0)
		return (-1.0);
	ref_dir = vec_k1v1_k2v2(2.0 * n_l, its_p->normal, -1.0, dir_pos2lgt);
	normalize(&ref_dir_n, &ref_dir);
	inverse_vec(&reverse_eyedir_vec, &eye2screen->unit_dir);
	normalize(&reverse_eyedir_vec_n, &reverse_eyedir_vec);
	return (dot_vec(&reverse_eyedir_vec_n, &ref_dir_n));
}

void	calc_spec_color(t_color *color, double v_r, t_light *light_info, t_obj_color obj_color)
{
	double	v_r_alpha;
	t_color	added_color;

	v_r_alpha = pow(v_r, obj_color.shininess);
	color_k1c1_pointer(&added_color, v_r_alpha, light_info->light_color);//ここおかしいっす
	color_add_pointer(color, color, &added_color);
}

double	ch_degrrralation(t_intersection_point *itsp, t_vec *pos2lgt, t_vec *eye)
{
	t_vec	plane2eye;

	if (is_equal_strings(itsp->obj->id_str, ID_PLANE))
	{
		neg_vec(&plane2eye, eye, &itsp->position);
		if ((dot(itsp->normal, *pos2lgt) >= 0 && dot(itsp->normal, plane2eye) < 0) || (dot(itsp->normal, *pos2lgt) < 0 && dot(itsp->normal, plane2eye) >= 0))
			return (-1.0);
		if (dot(itsp->normal, *pos2lgt) >= 0)
		{
			return (dot(itsp->normal, *pos2lgt));
		}
		else
		{
			inverse_vec(&itsp->normal, &itsp->normal);
			return (dot(itsp->normal, *pos2lgt));
		}
	}
	else
		return (dot(itsp->normal, *pos2lgt));
}

t_color	calc_specref(t_all_info *info, t_intersection_point	*its_p, t_ray eye2screen, t_color color)
{
	t_list	*light;
	t_light	*light_info;
	t_vec	dir_pos2lgt;
	t_vec	dir_pos2lgt_n;
	double	v_r;

	light = info->scene_info->lights;
	while (light != NULL)
	{
		//light_info = info->scene_info->lights->content;
		light_info = light->content;
		neg_vec(&dir_pos2lgt, &light_info->point, &its_p->position);
		if (is_obj_exists_between_itspos_and_light(info->scene_info, calc_diffuse_param(its_p, &eye2screen, light_info)) == false)
		{
			dir_pos2lgt_n = norm_vec(dir_pos2lgt);
			if ((SPOT_check(&dir_pos2lgt_n, light_info) == true && is_equal_strings(light_info->id_type, ID_SPOTLIGHT)) || is_equal_strings(light_info->id_type, ID_LIGHT))
			{
				v_r = calc_v_r(ch_degrrralation(its_p, &dir_pos2lgt_n, &info->camera_info->position), its_p, dir_pos2lgt_n, &eye2screen);
				if (v_r - 0.0 > EPSIRON)
					calc_spec_color(&color, v_r, light_info, its_p->obj->obj_color);
			}
		}
		light = light->next;
	}
	return (color);
}

t_color	calc_specular_reflection(t_all_info *info, t_intersection_point	*its_p, t_ray eye2screen)
{
	t_color	color;

	color_set(&color, 0.0, 0.0, 0.0);
	if (its_p->obj->obj_color.is_perfect_ref == true)
		return (color);
	//color_add(color, calc_specref(info, its_p, eye2screen, color));
	return (calc_specref(info, its_p, eye2screen, color));
}