/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/18 15:17:23 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// c + k1c1 * k2c2
t_color	color_mul_k1c1k2c2(double k1, t_color c1, \
						double k2, t_color c2)
{
	t_color	color;

	color.r = k1 * c1.r * k2 * c2.r;
	color.g = k1 * c1.g * k2 * c2.g;
	color.b = k1 * c1.b * k2 * c2.b;
	return (color);
}

t_color	color_k1c1_k2c2(double k1, t_color c1, \
						double k2, t_color c2)
{
	t_color	color;

	color.r = k1 * c1.r * k2 * c2.r;
	color.g = k1 * c1.g * k2 * c2.g;
	color.b = k1 * c1.b * k2 * c2.b;
	return (color);
}

t_color	color_k1c1(double k1, t_color c1)
{
	t_color	color;

	color.r = k1 * c1.r;
	color.g = k1 * c1.g;
	color.b = k1 * c1.b;
	return (color);
}

t_color	color_add(const t_color c1, t_color c2)
{
	t_color	color;

	color.r = c1.r + c2.r;
	color.g = c1.g + c2.g;
	color.b = c1.b + c2.b;
	return (color);
}

t_color	init_color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

void	colort_init_pointer(t_color *color)
{
	color->r = 0;
	color->g = 0;
	color->b = 0;
}
