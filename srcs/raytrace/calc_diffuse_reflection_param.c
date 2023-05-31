/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_diffuse_reflection_param.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:13:19 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:08:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec	get_normal(t_intersection_point *its_p)
{
	if (is_obj_bump_texture(its_p->obj->obj_color))
		return (get_bump_normal(its_p));
	return (its_p->normal);
}

// bump normal used calculate dot(normal, pos2light)
t_diffuse_param	calc_diffuse_param(t_intersection_point *its_p, \
									t_ray *ray, t_light *light)
{
	t_diffuse_param	p;
	t_vec			normal;

	p.ray = *ray;
	p.its_p = *its_p;
	p.light = light;
	p.vec_normal = its_p->normal;
	p.vec_pos2light = sub(light->point, its_p->position);
	p.unit_pos2light = norm_vec(p.vec_pos2light);
	p.unit_light2pos = inverse(p.unit_pos2light);
	normal = get_normal(its_p);
	p.dot_n_unit_pos2light = dot(normal, p.unit_pos2light);
	return (p);
}
