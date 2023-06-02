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

	return ((NORMAL_MIN <= x && x <= NORMAL_MAX) \
	&& (NORMAL_MIN <= y && y <= NORMAL_MAX) \
	&& (NORMAL_MIN <= z && z <= NORMAL_MAX));
}

// todo: del print
bool	is_vec_in_range(t_vec vec)
{
	const double	x = vec.x;
	const double	y = vec.y;
	const double	z = vec.z;

	if (isinf(x) || isnan(x))
	{
		printf("x(%f) out of range\n", x);
		return (false);
	}
	if (isinf(y) || isnan(y))
	{
		printf("y(%f) out of range\n", y);
		return (false);
	}
	if (isinf(z) || isnan(z))
	{
		printf("z(%f) out of range\n", z);
		return (false);
	}
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

// todo: del print
bool	is_num_in_valid_range(double num)
{
	if (num <= 0)
	{
		printf("%f <= 0\n", num);
		return (false);
	}
	if (isinf(num))
	{
		printf("%f is inf\n", num);
		return (false);
	}
	if (isnan(num))
	{
		printf("%f is nan\n", num);
		return (false);
	}
	return (true);
}

bool	is_ratio_in_range(double ratio)
{
	return (RATIO_MIN <= ratio && ratio <= RATIO_MAX);
}

bool	is_fov_in_range(double fov_degree)
{
	return (FOV_DEG_MIN <= fov_degree && fov_degree <= FOV_DEG_MAX);
}

bool	is_angle_in_range(double angle_degree)
{
	return (ANGLE_DEG_MIN <= angle_degree && angle_degree <= ANGLE_DEG_MAX);
}

bool	is_comment_line(char c)
{
	return (c == '#');
}
