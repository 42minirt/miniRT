/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_condition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:34:45 by takira            #+#    #+#             */
/*   Updated: 2023/05/18 17:50:36 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_bump_data_exists(t_obj_color obj_color)
{
	return (obj_color.bump_data.data != NULL);
}

bool	is_image_data_exists(t_obj_color obj_color)
{
	return (obj_color.texture_data.data != NULL);
}

// todo:tmp
bool	is_obj_exists_between_itspos_and_light(t_scene_info *scene, t_diffuse_param p)
{
	t_ray					shadow_ray;
	t_intersection_point	its_p;
	bool					is_obj_exists;
	double					search_distance;

	shadow_ray.pos = vec_k1v1_k2v2(1.0, p.its_p->position, EPSILON, p.vec_pos2light);
	shadow_ray.unit_dir = norm_vec(p.vec_pos2light);
	search_distance = norm(p.vec_pos2light) - EPSILON;
	is_obj_exists = check_intersection(scene, shadow_ray, &its_p);
	if (is_obj_exists && its_p.distance <= search_distance)
		return (true);
	return (false);
}

bool	is_obj_perfect_ref(t_intersection_point *its_p)
{
	return (its_p->obj->obj_color.is_perfect_ref);
}

bool	is_obj_checker(t_intersection_point *its_p)
{
	return (its_p->obj->obj_color.is_checker);
}
