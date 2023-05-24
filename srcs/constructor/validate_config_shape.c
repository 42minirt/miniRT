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
