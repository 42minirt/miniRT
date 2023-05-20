/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient_setting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//static bool	is_ambient_already_exists(t_scene_info *scene)
//{
//	return (scene->brightness >= 0);
//}

// #Ambient  lightning_ratio[0,1]  RGB[0,255]
t_parse_res	get_ambient_setting(const char *line, t_scene_info *scene)
{
	size_t	idx;

//	if (is_ambient_already_exists(scene))
//		return (ERROR_MULTIPLE_ID);
	idx = 0;
	if (parse_double(line, &scene->brightness, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_color(line, &scene->ambient_color, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}
