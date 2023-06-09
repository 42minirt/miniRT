/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constructor.h"
#include "typedef.h"
#include "minirt.h"

t_parse_res	get_config(const char *id_str, const char *line, t_all_info *all)
{
	t_parse_res	result;

	result = ERROR_FATAL;
	if (streq(id_str, ID_CAMERA))
		result = get_congfig_of_camera(line, all->camera_info);
	else if (streq(id_str, ID_AMBIENT))
		result = get_config_of_ambient(line, all->scene_info);
	else if (streq(id_str, ID_LIGHT) \
	|| streq(id_str, ID_SPOTLIGHT))
		result = get_config_of_lights(line, all->scene_info, id_str);
	else if (streq(id_str, ID_PLANE) \
	|| streq(id_str, ID_SPHERE) \
	|| streq(id_str, ID_CYLINDER) \
	|| streq(id_str, ID_CORN))
		result = get_config_of_objects(line, all->scene_info, id_str);
	return (result);
}
