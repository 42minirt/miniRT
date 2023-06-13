/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:16:19 by user              #+#    #+#             */
/*   Updated: 2023/06/13 23:27:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	setvec(t_vec *tgt_vec, double x, double y, double z)
{
	tgt_vec->x = x;
	tgt_vec->y = y;
	tgt_vec->z = z;
}

void	inverse_vec(t_vec *inv_vec, t_vec *inved_vec)
{
	setvec(
		inv_vec,
		inved_vec->x * (-1),
		inved_vec->y * (-1),
		inved_vec->z * (-1));
}

double	obtain_vecsize(t_vec *vec)
{
	double	vec_size;

	vec_size = sqrt(\
	pow(vec->x, 2) + \
	pow(vec->y, 2) + \
	pow(vec->z, 2));
	return (vec_size);
}

void	times_vec(t_vec *tgt_vec, double t, t_vec *sub)
{
	setvec(\
		tgt_vec,
		t * sub->x,
		t * sub->y,
		t * sub->z);
}
