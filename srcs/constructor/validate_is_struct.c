/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_vec_in_normal_range(t_vec vec)
{
	if (norm(vec) < (1.0 / EPSILON_DIVISOR))
		return (false);
	return ((NORMAL_MIN <= vec.x && vec.x <= NORMAL_MAX) \
	&& (NORMAL_MIN <= vec.y && vec.y <= NORMAL_MAX) \
	&& (NORMAL_MIN <= vec.z && vec.z <= NORMAL_MAX));
}

bool	is_vec_in_double_range(t_vec vec)
{
	if (isinf(vec.x) || isnan(vec.x))
		return (false);
	if (isinf(vec.y) || isnan(vec.y))
		return (false);
	if (isinf(vec.z) || isnan(vec.z))
		return (false);
	return (true);
}

bool	is_color_in_range(t_color color)
{
	return ((0.0 <= color.r && color.r <= 255.0) \
	&& (0.0 <= color.g && color.g <= 255.0) \
	&& (0.0 <= color.b && color.b <= 255.0));
}
