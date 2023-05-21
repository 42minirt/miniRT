/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_condition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:34:45 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:32:44 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// todo:tmp
bool	is_obj_exists_between_itspos_and_light(t_scene_info *scene, t_diffuse_param p)
{
	t_ray					shadow_ray;
	t_intersection_point	tmp_its_p;
	bool					is_obj_exists;
	double					search_distance;

	shadow_ray.pos = vec_k1v1_k2v2(1.0, p.its_p.position, EPSILON, p.vec_pos2light);
	shadow_ray.unit_dir = p.vec_pos2light;
	search_distance = norm(p.vec_pos2light) - EPSILON;
	is_obj_exists = check_intersection(scene, shadow_ray, &tmp_its_p);
	if (is_obj_exists && tmp_its_p.distance <= search_distance)
		return (true);
	return (false);
}

bool	is_obj_perfect_ref(t_obj_color obj_color)
{
	return (obj_color.is_perfect_ref);
}

bool	is_obj_checker(t_obj_color obj_color)
{
	return (obj_color.is_checker);
}

bool	is_obj_bump_texture(t_obj_color obj_color)
{
	return (obj_color.is_bump);
}

bool	is_obj_image_texture(t_obj_color obj_color)
{
	return (obj_color.is_texture);
}
