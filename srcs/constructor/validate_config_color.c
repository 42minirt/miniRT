/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:37:09 by user              #+#    #+#             */
/*   Updated: 2023/05/20 20:37:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parse_res	validate_obj_color(t_obj *obj)
{
	if (!is_color_in_range(obj->obj_color.kd))
		return (ERROR_OUT_OF_RANGE);
	if (obj->obj_color.is_checker \
	&& !is_color_in_range(obj->obj_color.checker_color))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}
