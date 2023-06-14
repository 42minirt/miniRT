/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_of_camera.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// #Camera  viewpoint(xyz)  normalized_orientation_vec[-1,1]  FOV[0,180]
t_parse_res	get_congfig_of_camera(const char *line, t_camera_info *camera)
{
	size_t		idx;
	t_parse_res	res;

	idx = 0;
	res = parse_vec(line, &camera->position, &idx);
	if (res != PASS)
		return (res);
	res = parse_vec(line, &camera->direction, &idx);
	if (res != PASS)
		return (res);
	res = parse_double(line, &camera->fov_deg, &idx);
	if (res != PASS)
		return (res);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}
