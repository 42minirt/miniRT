/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_id_cnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:10:44 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constructor.h"
#include "typedef.h"

t_id_cnt	init_id_cnt(void)
{
	t_id_cnt	cnt;

	cnt.camera_cnt = 0;
	cnt.ambient_cnt = 0;
	cnt.point_light_cnt = 0;
	cnt.spot_light_cnt = 0;
	cnt.sphere_cnt = 0;
	cnt.plane_cnt = 0;
	cnt.cylinder_cnt = 0;
	cnt.corn_cnt = 0;
	return (cnt);
}

t_parse_res	validate_id_cnt(t_id_cnt cnt)
{
	if (cnt.camera_cnt == 1 && cnt.ambient_cnt == 1)
		return (PASS);
	if (cnt.camera_cnt == 0)
		return (ERROR_MISSING_ID);
	if (cnt.camera_cnt > 1)
		return (ERROR_MULTIPLE_ID);
	if (cnt.ambient_cnt == 0)
		return (ERROR_MISSING_ID);
	if (cnt.ambient_cnt > 1)
		return (ERROR_MULTIPLE_ID);
	return (ERROR_FATAL);
}

void	increment_id_cnt(const char *id_str, t_id_cnt *cnt)
{
	if (streq(id_str, ID_AMBIENT))
		cnt->ambient_cnt++;
	else if (streq(id_str, ID_CAMERA))
		cnt->camera_cnt++;
	else if (streq(id_str, ID_LIGHT))
		cnt->spot_light_cnt++;
	else if (streq(id_str, ID_SPOTLIGHT))
		cnt->point_light_cnt++;
	else if (streq(id_str, ID_SPHERE))
		cnt->sphere_cnt++;
	else if (streq(id_str, ID_PLANE))
		cnt->plane_cnt++;
	else if (streq(id_str, ID_CYLINDER))
		cnt->cylinder_cnt++;
	else if (streq(id_str, ID_CORN))
		cnt->corn_cnt++;
}

t_parse_res	validate_id(const char *id_str)
{
	if (streq(id_str, ID_AMBIENT))
		return (PASS);
	if (streq(id_str, ID_CAMERA))
		return (PASS);
	if (streq(id_str, ID_LIGHT))
		return (PASS);
	if (streq(id_str, ID_SPOTLIGHT))
		return (PASS);
	if (streq(id_str, ID_SPHERE))
		return (PASS);
	if (streq(id_str, ID_PLANE))
		return (PASS);
	if (streq(id_str, ID_CYLINDER))
		return (PASS);
	if (streq(id_str, ID_CORN))
		return (PASS);
	return (ERROR_INVALID_TYPE);
}
