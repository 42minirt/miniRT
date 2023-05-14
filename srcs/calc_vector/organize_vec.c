/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:16:19 by user              #+#    #+#             */
/*   Updated: 2023/05/14 23:26:27 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void	setvec(t_vec *tgt_vec, double x, double y, double z)
{
	tgt_vec->x = x;
	tgt_vec->y = y;
	tgt_vec->z = z;
}

void	normalize(t_vec *normal_vec, t_vec *normarized_vec)
{
	double	vec_size;

	vec_size = sqrt(
		pow(normarized_vec->x, 2) \
		+ pow(normarized_vec->y, 2) \
		+ pow(normarized_vec->z, 2));
	if (vec_size == 0.0)
	{
		printf("this size 0 ! So exit");
		exit(1);
	}
	setvec(
		normal_vec,
		normarized_vec->x / vec_size,
		normarized_vec->y / vec_size,
		normarized_vec->z / vec_size
	);
}

void	inverse_vec(t_vec *inv_vec, t_vec *inved_vec)
{
	setvec(
		inv_vec,
		inved_vec->x * (-1),
		inved_vec->y * (-1),
		inved_vec->z * (-1)
	);
}