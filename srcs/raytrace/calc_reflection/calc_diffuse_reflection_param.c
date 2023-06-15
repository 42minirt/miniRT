/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_diffuse_reflection_param.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:13:19 by takira            #+#    #+#             */
/*   Updated: 2023/06/14 01:15:53 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "raytrace.h"
#include "vector.h"

t_vec	get_normal(t_intersection_point *its_p)
{
	if (is_obj_bump_texture(its_p->obj->obj_color))
		return (get_bump_normal(its_p));
	return (its_p->normal);
}

// bump normal used calculate dot(normal, pos2light)
// Drawable: dot(n, l) when n is bump or normal > 0 && normal is drawable
t_diffuse_param	calc_diffuse_param(t_intersection_point *its_p, \
									t_ray *ray, \
									t_light *light)
{
	t_diffuse_param	p;

	p.ray = *ray;
	p.its_p = *its_p;
	p.light = light;
	p.vec_pos2light = sub(light->point, its_p->position);
	p.unit_pos2light = norm_vec(p.vec_pos2light);
	p.unit_light2pos = inverse(p.unit_pos2light);
	p.dot_n_unit_pos2light = calc_dot_n_l(*its_p, *ray, p.unit_pos2light);
	return (p);
}
