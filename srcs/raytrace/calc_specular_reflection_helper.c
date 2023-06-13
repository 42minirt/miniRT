/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_specular_reflection_helper.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 01:39:32 by user              #+#    #+#             */
/*   Updated: 2023/06/14 01:45:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	spot_check(t_vec *dir_pos2lgt_n, t_light *lgt_inf)
{
	t_vec	pos2lgt;
	double	alpha;

	inverse_vec(&pos2lgt, dir_pos2lgt_n);
	alpha = acos(dot_vec(&pos2lgt, &lgt_inf->direction));
	if (alpha > lgt_inf->sl_angle / 2.0f * M_PI / 180.0)
		return (false);
	return (true);
}

t_color	calc_specref(t_all_info *info, \
t_intersection_point	*its_p, t_ray eye2screen, t_color color)
{
	t_list	*light;
	t_light	*light_info;
	t_vec	dir_pos2lgt;
	t_vec	dir_pos2lgt_n;

	light = info->scene_info->lights;
	while (light != NULL)
	{
		light_info = light->content;
		neg_vec(&dir_pos2lgt, &light_info->point, &its_p->position);
		if (is_obj_exists_between_itspos_and_light(info->scene_info, \
		calc_diffuse_param(its_p, &eye2screen, light_info)) == false)
		{
			dir_pos2lgt_n = norm_vec(dir_pos2lgt);
			if ((spot_check(&dir_pos2lgt_n, light_info) == true && \
			is_equal_strings(light_info->id_type, ID_SPOTLIGHT)) || \
			is_equal_strings(light_info->id_type, ID_LIGHT))
				calc_specrefhelper(&color, calc_v_r(calc_dot_n_l(*its_p, \
				eye2screen, dir_pos2lgt_n), its_p, dir_pos2lgt_n, &eye2screen), \
				light_info, its_p->obj->obj_color);
		}
		light = light->next;
	}
	return (color);
}
