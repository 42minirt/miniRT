/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:11:11 by user              #+#    #+#             */
/*   Updated: 2023/05/21 17:49:02 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_vec(t_vec *sub, t_vec *v1, t_vec *v2)
{
	setvec(sub, v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

void	neg_vec(t_vec *sub, t_vec *v1, t_vec *v2)
{
	setvec(sub, v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}

double	dot_vec(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

void	calc_outerproduct(t_vec *tgt_vec, t_vec *v1, t_vec *v2)
{
	setvec(
		tgt_vec,
		v1->y * v2->z - v1->z * v2->y, \
		v1->z * v2->x - v1->x * v2->z, \
		v1->x * v2->y - v1->y * v2->x \
	);
}

void	t_mix_vec_all(t_vec *tgt_vec, double t1, \
t_vec *v1, double t2, t_vec *v2)
{
	setvec(tgt_vec, \
	t1 * v1->x + t2 * v2->x, \
	t1 * v1->y + t2 * v2->y, \
	t1 * v1->z + t2 * v2->z);
}
