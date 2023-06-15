/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_of_each_obj.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/24 21:38:03 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constructor.h"
#include "color.h"
#include "typedef.h"
#include "minirt.h"

// sp   XYZ                    diameter            RGB[0,255]   <OPTION>
static t_parse_res	get_sphere_config(const char *line, t_obj *obj, size_t *idx)
{
	t_parse_res	res;

	res = parse_vec(line, &obj->shape_data.sphere.center, idx);
	if (res != PASS)
		return (res);
	res = parse_double(line, &obj->shape_data.sphere.diameter, idx);
	if (res != PASS)
		return (res);
	res = parse_color(line, &obj->obj_color.kd, idx);
	if (res != PASS)
		return (res);
	return (PASS);
}

// pl   XYZ   norm_vec[-1,1]                       RGB[0,255]   <OPTION>
static t_parse_res	get_plane_config(const char *line, t_obj *obj, size_t *idx)
{
	t_parse_res	res;

	res = parse_vec(line, &obj->shape_data.plane.center, idx);
	if (res != PASS)
		return (res);
	res = parse_vec(line, &obj->shape_data.plane.normal, idx);
	if (res != PASS)
		return (res);
	res = parse_color(line, &obj->obj_color.kd, idx);
	if (res != PASS)
		return (res);
	obj->obj_color.ks = init_color_hex(KS_COLOR_PLANE);
	return (PASS);
}

// cy   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION>
static t_parse_res	get_cylinder_config(const char *line, \
										t_obj *obj, size_t *idx)
{
	t_parse_res	res;

	res = parse_vec(line, &obj->shape_data.cylinder.bottom_center, idx);
	if (res != PASS)
		return (res);
	res = parse_vec(line, &obj->shape_data.cylinder.axis, idx);
	if (res != PASS)
		return (res);
	res = parse_double(line, &obj->shape_data.cylinder.diameter, idx);
	if (res != PASS)
		return (res);
	res = parse_double(line, &obj->shape_data.cylinder.height, idx);
	if (res != PASS)
		return (res);
	res = parse_color(line, &obj->obj_color.kd, idx);
	if (res != PASS)
		return (res);
	return (PASS);
}

// co   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION>
static t_parse_res	get_corn_config(const char *line, t_obj *obj, size_t *idx)
{
	t_parse_res	res;

	res = parse_vec(line, &obj->shape_data.corn.bottom_center, idx);
	if (res != PASS)
		return (res);
	res = parse_vec(line, &obj->shape_data.corn.axis, idx);
	if (res != PASS)
		return (res);
	res = parse_double(line, &obj->shape_data.corn.diameter, idx);
	if (res != PASS)
		return (res);
	res = parse_double(line, &obj->shape_data.corn.height, idx);
	if (res != PASS)
		return (res);
	res = parse_color(line, &obj->obj_color.kd, idx);
	if (res != PASS)
		return (res);
	return (PASS);
}

t_parse_res	get_config_of_each_obj(const char *line, t_obj *obj)
{
	t_parse_res	res;
	size_t		idx;

	idx = 0;
	res = ERROR_FATAL;
	if (is_equal_strings(obj->id_str, ID_SPHERE))
		res = get_sphere_config(line, obj, &idx);
	else if (is_equal_strings(obj->id_str, ID_PLANE))
		res = get_plane_config(line, obj, &idx);
	else if (is_equal_strings(obj->id_str, ID_CYLINDER))
		res = get_cylinder_config(line, obj, &idx);
	else if (is_equal_strings(obj->id_str, ID_CORN))
		res = get_corn_config(line, obj, &idx);
	if (res != PASS)
		return (res);
	if (!line[idx])
		return (PASS);
	res = get_bonus_config_of_obj(line, obj, &idx);
	if (res != PASS)
		return (res);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (res);
}
