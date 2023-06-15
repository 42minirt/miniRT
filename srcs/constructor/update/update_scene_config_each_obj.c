/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene_config_each_obj.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/22 22:48:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.h"
#include "vector.h"

void	update_scene_sphere_info(t_sphere *sphere)
{
	sphere->radius = sphere->diameter / 2.0;
}

void	update_scene_plane_info(t_plane *plane)
{
	plane->normal = norm_vec(plane->normal);
}

void	update_scene_cylinder_info(t_cylinder *cylinder)
{
	cylinder->radius = cylinder->diameter / 2.0;
	cylinder->axis = norm_vec(cylinder->axis);
}

void	update_scene_corn_info(t_corn *corn)
{
	corn->radius = corn->diameter / 2.0;
	corn->axis = norm_vec(corn->axis);
	corn->origin = add(corn->bottom_center, k_vec(corn->height, corn->axis));
}
