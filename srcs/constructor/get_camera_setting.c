/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera_setting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//static bool	is_camera_already_exists(t_camera_info *camera)
//{
//	return (camera->fov_deg >= 0);
//}

// #Camera  viewpoint(xyz)  normalized_orientation_vec[-1,1]  FOV[0,180]
t_parse_res	get_camera_setting(const char *line, t_camera_info *camera)
{
	size_t	idx;

//	if (is_camera_already_exists(camera))
//		return (ERROR_MULTIPLE_ID);
	idx = 0;
	if (parse_vec(line, &camera->position, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parse_vec(line, &camera->direction, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parse_double(line, &camera->fov_deg, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}
