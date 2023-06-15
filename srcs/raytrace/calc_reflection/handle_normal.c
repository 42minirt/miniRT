/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 01:48:45 by user              #+#    #+#             */
/*   Updated: 2023/06/14 01:49:33 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "raytrace.h"
#include "vector.h"

static bool	is_same_dir_pos2eye_pos2light(t_vec original_normal, \
											t_ray ray, \
											t_vec unit_pos2light)
{
	double	dot_normal_invdir;
	double	dot_normal_pos2light;

	dot_normal_invdir = dot(original_normal, inverse(ray.unit_dir));
	dot_normal_pos2light = dot(original_normal, unit_pos2light);
	if (dot_normal_invdir * dot_normal_pos2light <= 0)
		return (false);
	return (true);
}

double	calc_dot_n_l(t_intersection_point itsp, t_ray ray, t_vec unit_pos2light)
{
	const t_vec	original_normal = itsp.normal;
	t_vec		normal_to_calc;
	double		dot_normal_pos2light;

	normal_to_calc = get_normal(&itsp);
	dot_normal_pos2light = dot(normal_to_calc, unit_pos2light);
	if (dot_normal_pos2light <= 0)
		return (-1.0);
	if (!is_same_dir_pos2eye_pos2light(original_normal, ray, unit_pos2light))
		return (-1.0);
	return (dot_normal_pos2light);
}

//ADD: handle plane and sphere normal, n or inv(n)
t_vec	get_pl_sp_drawable_normal(t_intersection_point itsp, t_vec ray_dir)
{
	if (!streq(itsp.obj->id_str, ID_PLANE) \
 && !streq(itsp.obj->id_str, ID_SPHERE))
		return (itsp.normal);
	if (dot(itsp.normal, inverse(ray_dir)) >= 0.0)
		return (itsp.normal);
	return (inverse(itsp.normal));
}
