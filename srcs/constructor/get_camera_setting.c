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

// #Camera     viewpoint(xyz)         normalized_orientation_vec[-1,1]   FOV[0,180]
t_parse_res	get_camera_setting(const char *line, t_camera_info *camera)
{
	(void)line;
	(void)camera;
	// todo: already exists
	return (PASS);
}
