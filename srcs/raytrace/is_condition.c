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

// todo : 共通
bool	is_obj_exists_extension_of_ray(t_scene_info *scene, t_diffuse_param p)
{

}

bool	is_obj_perfect_ref(t_intersection_point *its_p)
{
	return (its_p->obj->obj_color.is_perfect_ref);
}
