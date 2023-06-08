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

bool	is_ratio_in_range(double ratio)
{
	return (RATIO_MIN <= ratio && ratio <= RATIO_MAX);
}

bool	is_fov_in_range(double fov_degree)
{
	return (FOV_DEG_MIN < fov_degree && fov_degree < FOV_DEG_MAX);
}

bool	is_angle_in_range(double angle_degree)
{
	return (ANGLE_DEG_MIN <= angle_degree && angle_degree <= ANGLE_DEG_MAX);
}

bool	is_num_in_valid_range(double num)
{
	if (num <= 0)
		return (false);
	if (isinf(num))
		return (false);
	if (isnan(num))
		return (false);
	return (true);
}

bool	is_comment_line(char c)
{
	return (c == '#');
}
