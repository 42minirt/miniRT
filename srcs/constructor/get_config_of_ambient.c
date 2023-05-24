/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_of_ambient.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// #Ambient  lightning_ratio[0,1]  RGB[0,255]
t_parse_res	get_config_of_ambient(const char *line, t_scene_info *scene)
{
	size_t		idx;
	t_parse_res	res;

	idx = 0;
	res = parse_double(line, &scene->brightness, &idx);
	if (res != PASS)
		return (res);
	res = parse_color(line, &scene->ambient_color, &idx);
	if (res != PASS)
		return (res);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}
