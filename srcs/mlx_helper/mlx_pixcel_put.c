/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixcel_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:16:06 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	clamp(double num, double min, double max)
{
	if (num <= min)
		return (min);
	if (max <= num)
		return (max);
	return (num);
}

void	put_pixel(t_mlx_info *mlx_info, size_t x, size_t y, t_color c)
{
	char	*dst;
	int		int_color;

	int_color = (int)(255 * clamp(c.r, 0.0, 1.0)) << 16 \
				| (int)(255 * clamp(c.g, 0.0, 1.0)) << 8 \
				| (int)(255 * clamp(c.b, 0.0, 1.0));
	dst = mlx_info->addr \
			+ (y * mlx_info->line_length + x * (mlx_info->bits_per_pixel / 8));
	*(unsigned int *)dst = int_color;
}
