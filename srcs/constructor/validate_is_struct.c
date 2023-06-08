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

bool	is_normal_vec_in_range(t_vec vec)
{
	const double	x = vec.x;
	const double	y = vec.y;
	const double	z = vec.z;

	if (norm(vec) < (1.0 / EPSILON_DIVISOR))
		return (false);
	return ((NORMAL_MIN <= x && x <= NORMAL_MAX) \
	&& (NORMAL_MIN <= y && y <= NORMAL_MAX) \
	&& (NORMAL_MIN <= z && z <= NORMAL_MAX));
}

bool	is_vec_in_range(t_vec vec)
{
	const double	x = vec.x;
	const double	y = vec.y;
	const double	z = vec.z;

	if (isinf(x) || isnan(x))
		return (false);
	if (isinf(y) || isnan(y))
		return (false);
	if (isinf(z) || isnan(z))
		return (false);
	return (true);
}

bool	is_color_in_range(t_color color)
{
	const double	r = color.r;
	const double	g = color.g;
	const double	b = color.b;

	return ((0.0 <= r && r <= 255.0) \
	&& (0.0 <= g && g <= 255.0) \
	&& (0.0 <= b && b <= 255.0));
}
