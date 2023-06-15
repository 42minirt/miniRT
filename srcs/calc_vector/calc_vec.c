/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	normalize(t_vec *normal_vec, t_vec *normarized_vec)
{
	double	vec_size;

	vec_size = sqrt(
			pow(normarized_vec->x, 2) \
		+ pow(normarized_vec->y, 2) \
		+ pow(normarized_vec->z, 2));
	if (vec_size == 0.0)
	{
		printf("[Error] division by zero in normalize.\n");
		exit(1);
	}
	setvec(normal_vec, \
	normarized_vec->x / vec_size, \
	normarized_vec->y / vec_size, \
	normarized_vec->z / vec_size);
}

void	vector_scalar_product(t_vec *tgt_vec, double k, t_vec *v)
{
	setvec(tgt_vec, k * v->x, k * v->y, k * v->z);
}

t_vec	k_vec(double k, t_vec v)
{
	t_vec	ret;

	vector_scalar_product(&ret, k, &v);
	return (ret);
}

double	norm(t_vec vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

t_vec	norm_vec(t_vec v)
{
	t_vec	ret;

	normalize(&ret, &v);
	return (ret);
}
