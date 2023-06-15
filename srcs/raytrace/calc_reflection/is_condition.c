/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_condition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:34:45 by takira            #+#    #+#             */
/*   Updated: 2023/06/14 01:48:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "raytrace.h"
#include "vector.h"

bool	is_obj_btw_pos_light(t_scene_info *scene, \
								t_vec pos, \
								t_vec pos2light)
{
	t_ray					shadow_ray;
	t_intersection_point	tmp_its_p;
	bool					is_obj_exists;
	double					search_distance;

	shadow_ray.pos = vec_k1v1_k2v2(1.0, pos, \
									1.0 / EPSILON_DIVISOR, norm_vec(pos2light));
	shadow_ray.unit_dir = norm_vec(pos2light);
	search_distance = norm(pos2light) - (1.0 / EPSILON_DIVISOR);
	is_obj_exists = check_intersection(scene, shadow_ray, &tmp_its_p, true);
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
	return (obj_color.is_bump && obj_color.bump_data.data);
}

bool	is_obj_image_texture(t_obj_color obj_color)
{
	return (obj_color.is_texture && obj_color.texture_data.data);
}
