/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:36:51 by user              #+#    #+#             */
/*   Updated: 2023/05/20 20:36:52 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_vec_in_normal_range(t_vec vec)
{
	const double	x = vec.x;
	const double	y = vec.y;
	const double	z = vec.z;

	return ((-1.0 <= x && x <= 1.0) \
	&& (-1.0 <= y && y <= 1.0) \
	&& (-1.0 <= z && z <= 1.0));
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

bool	is_ratio_in_range(double ratio)
{
	return (0.0 <= ratio && ratio <= 1.0);
}

bool	is_angle_in_range(double ratio)
{
	return (0.0 <= ratio && ratio <= 180.0);
}
