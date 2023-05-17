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

#include "minirt.h"

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
		inved_vec->z * (-1)
	);
}
