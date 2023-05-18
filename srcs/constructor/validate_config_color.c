/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
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
