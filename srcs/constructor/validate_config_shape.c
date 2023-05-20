/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config_shape.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:37:14 by user              #+#    #+#             */
/*   Updated: 2023/05/20 20:37:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_parse_res	validate_sphere(t_sphere *sphere)
{
	if (sphere->diameter <= 0.0)
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_plane(t_plane *plane)
{
	if (!is_vec_in_normal_range(plane->normal))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_cylinder(t_cylinder *cylinder)
{
	if (!is_vec_in_normal_range(cylinder->axis))
		return (ERROR_OUT_OF_RANGE);
	if (cylinder->diameter <= 0.0)
		return (ERROR_OUT_OF_RANGE);
	if (cylinder->height <= 0.0)
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_corn(t_corn *corn)
{
	if (!is_vec_in_normal_range(corn->axis))
		return (ERROR_OUT_OF_RANGE);
	if (corn->diameter <= 0.0)
		return (ERROR_OUT_OF_RANGE);
	if (corn->height <= 0.0)
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

t_parse_res	validate_obj_shape(t_obj *obj)
{
	if (obj->type == BALL)
		return (validate_sphere(&obj->shape_data.sphere));
	if (obj->type == PLANE)
		return (validate_plane(&obj->shape_data.plane));
	if (obj->type == CYLINDER)
		return (validate_cylinder(&obj->shape_data.cylinder));
	if (obj->type == CORN)
		return (validate_corn(&obj->shape_data.corn));
	return (ERROR_INVALID_TYPE);
}
