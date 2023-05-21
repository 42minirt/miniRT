/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:13:00 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_parse_res	get_config(const char *id_str, \
										const char *line, t_all_info *all)
{
	t_parse_res	result;

	result = ERROR_FATAL;
	if (is_equal_strings(id_str, ID_CAMERA))
		result = get_congfig_of_camera(line, all->camera_info);
	else if (is_equal_strings(id_str, ID_AMBIENT))
		result = get_config_of_ambient(line, all->scene_info);
	else if (is_equal_strings(id_str, ID_LIGHT) \
			|| is_equal_strings(id_str, ID_SPOTLIGHT))
		result = get_config_of_lights(line, all->scene_info, id_str);
	else if (is_equal_strings(id_str, ID_PLANE) \
			|| is_equal_strings(id_str, ID_SPHERE) \
			|| is_equal_strings(id_str, ID_CYLINDER) \
			|| is_equal_strings(id_str, ID_CORN))
		result = get_config_of_objects(line, all->scene_info, id_str);
	return (result);
}
