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

#include "minirt.h"

static t_parse_res	validate_sphere_shape(t_sphere *sphere)
{
	if (!is_vec_in_double_range(sphere->center))
		return (ERROR_OUT_OF_RANGE);
	if (!is_num_in_valid_range(sphere->diameter))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_plane_shape(t_plane *plane)
{
	if (!is_vec_in_double_range(plane->center))
		return (ERROR_OUT_OF_RANGE);
	if (!is_vec_in_normal_range(plane->normal))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_cylinder_shape(t_cylinder *cylinder)
{
	double	radius;
	t_vec	top;

	if (!is_vec_in_double_range(cylinder->bottom_center))
		return (ERROR_OUT_OF_RANGE);
	if (!is_vec_in_normal_range(cylinder->axis))
		return (ERROR_OUT_OF_RANGE);
	if (!is_num_in_valid_range(cylinder->diameter))
		return (ERROR_OUT_OF_RANGE);
	if (!is_num_in_valid_range(cylinder->height))
		return (ERROR_OUT_OF_RANGE);
	radius = cylinder->diameter / 2.0;
	if (radius / cylinder->height <= (1.0 / EPSILON_DIVISOR))
		return (ERROR_OUT_OF_RANGE);
	top = add(cylinder->bottom_center, k_vec(cylinder->height, cylinder->axis));
	if (!is_vec_in_double_range(top))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

static t_parse_res	validate_corn_shape(t_corn *corn)
{
	double	radius;
	t_vec	origin;

	if (!is_vec_in_double_range(corn->bottom_center))
		return (ERROR_OUT_OF_RANGE);
	if (!is_vec_in_normal_range(corn->axis))
		return (ERROR_OUT_OF_RANGE);
	if (!is_num_in_valid_range(corn->diameter))
		return (ERROR_OUT_OF_RANGE);
	if (!is_num_in_valid_range(corn->height))
		return (ERROR_OUT_OF_RANGE);
	radius = corn->diameter / 2.0;
	if (radius / corn->height <= 1.0 / EPSILON_DIVISOR)
		return (ERROR_OUT_OF_RANGE);
	origin = add(corn->bottom_center, k_vec(corn->height, corn->axis));
	if (!is_vec_in_double_range(origin))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

t_parse_res	validate_obj_shape(t_obj *obj)
{
	if (is_equal_strings(obj->id_str, ID_SPHERE))
		return (validate_sphere_shape(&obj->shape_data.sphere));
	if (is_equal_strings(obj->id_str, ID_PLANE))
		return (validate_plane_shape(&obj->shape_data.plane));
	if (is_equal_strings(obj->id_str, ID_CYLINDER))
		return (validate_cylinder_shape(&obj->shape_data.cylinder));
	if (is_equal_strings(obj->id_str, ID_CORN))
		return (validate_corn_shape(&obj->shape_data.corn));
	return (ERROR_INVALID_TYPE);
}
