/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checker_ref_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:39:36 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 21:30:49 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	get_checker_freq(t_obj *obj, int *freq_u, int *freq_v)
{
	*freq_u = CHECKER_U_FREQ;
	*freq_v = CHECKER_V_FREQ;
	if (is_equal_strings(obj->id_str, ID_PLANE))
	{
		*freq_u /= 5;
		*freq_v /= 5;
	}
}

t_color	get_itspos_checker_color(t_intersection_point its_p)
{
	t_tangetnt_map	map;
	int				pattern_a;
	int				freq_u;
	int				freq_v;

	if (!is_obj_checker(its_p.obj->obj_color))
		return (init_color(0.0, 0.0, 0.0));
	map = get_tangent_coordinate_map(&its_p);
	get_checker_freq(its_p.obj, &freq_u, &freq_v);
	pattern_a = (int)(floor(map.u * freq_u) + floor(map.v * freq_v)) % 2;
	if (pattern_a)
		return (its_p.obj->obj_color.checker_color);
	return (its_p.obj->obj_color.kd);
}
