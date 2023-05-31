/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config_shape.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_parse_res	validate_sphere(t_sphere *sphere)
{
	if (!is_vec_in_range(sphere->center))
	{
		printf("sp vec out of range, (%f,%f,%f)\n", sphere->center.x, sphere->center.y, sphere->center.z);
		return (ERROR_OUT_OF_RANGE);
	}
	if (!is_num_in_valid_range(sphere->diameter))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_plane(t_plane *plane)
{
	if (!is_vec_in_range(plane->center))
	{
		printf("pl vec out of range, (%f,%f,%f)\n", plane->center.x, plane->center.y, plane->center.z);
		return (ERROR_OUT_OF_RANGE);
	}
	if (!is_normal_vec_in_range(plane->normal))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_cylinder(t_cylinder *cylinder)
{
	if (!is_vec_in_range(cylinder->bottom_center))
		return (ERROR_OUT_OF_RANGE);
	if (!is_normal_vec_in_range(cylinder->axis))
		return (ERROR_OUT_OF_RANGE);
	if (!is_num_in_valid_range(cylinder->diameter))
		return (ERROR_OUT_OF_RANGE);
	if (!is_num_in_valid_range(cylinder->height))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

//todo: check is_vec_in_range(corn->origin)
static t_parse_res	validate_corn(t_corn *corn)
{
	if (!is_vec_in_range(corn->bottom_center))
		return (ERROR_OUT_OF_RANGE);
	if (!is_normal_vec_in_range(corn->axis))
		return (ERROR_OUT_OF_RANGE);
	if (!is_num_in_valid_range(corn->diameter))
		return (ERROR_OUT_OF_RANGE);
	if (!is_num_in_valid_range(corn->height))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

t_parse_res	validate_obj_shape(t_obj *obj)
{
	if (is_equal_strings(obj->id_str, ID_SPHERE))
		return (validate_sphere(&obj->shape_data.sphere));
	if (is_equal_strings(obj->id_str, ID_PLANE))
		return (validate_plane(&obj->shape_data.plane));
	if (is_equal_strings(obj->id_str, ID_CYLINDER))
		return (validate_cylinder(&obj->shape_data.cylinder));
	if (is_equal_strings(obj->id_str, ID_CORN))
		return (validate_corn(&obj->shape_data.corn));
	return (ERROR_INVALID_TYPE);
}
