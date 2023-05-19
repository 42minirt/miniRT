/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_diffuse_reflection_param.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:13:19 by takira            #+#    #+#             */
/*   Updated: 2023/05/18 17:42:12 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec	get_normal(t_intersection_point *its_p)
{
	// todo: init_obj()でdata=NULLにしているのに入ってくる
	// とりあえず、is_bump flagを持たせて対応
	if (is_bump_data_exists(its_p->obj->obj_color))
	{
		return (get_bump_normal(its_p));
	}
	return (its_p->normal);
}

t_diffuse_param	calc_diffuse_param(t_intersection_point *its_p, \
								t_ray *ray, t_light *light)
{
	t_diffuse_param	p;
//	printf(" its_pos(%s) (x,y,z)=(%f,%f,%f)\n", __func__, its_p->position.x, its_p->position.y, its_p->position.z);

	p.ray = *ray;
	p.its_p = *its_p;
	p.light = light;

	p.vec_normal = get_normal(its_p);
	p.vec_pos2light = sub(light->point, its_p->position);
	p.vec_pos2light = norm_vec(p.vec_pos2light);
	p.vec_light2pos = inverse(p.vec_pos2light);
	p.vec_specular = norm_vec(p.vec_light2pos);

	p.dot_n_pos2light = dot(its_p->normal, p.vec_pos2light);
	return (p);
}
