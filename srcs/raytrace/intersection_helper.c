/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:26:06 by user              #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// t1 < t2
// if D == 0; t1 == t2
void	solve_quadratic_equation(t_d_param *d_param)
{
	const double	a = d_param->a;
	const double	b = d_param->b;
	const double	d = d_param->d;

	d_param->t1 = (-b - sqrt(d)) / (2.0 * a);
	d_param->t2 = (-b + sqrt(d)) / (2.0 * a);
}

double	get_valid_distance(double t1, double t2)
{
	if (0.0 < t1)
		return (t1);
	else if (0.0 < t2)
		return (t2);
	return (-1.0);
}

double	calc_discriminant(double a, double b, double c)
{
	return (pow(b, 2) - 4.0 * a * c);
}
