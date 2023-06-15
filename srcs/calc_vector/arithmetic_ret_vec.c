/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_ret_vec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:34:45 by user              #+#    #+#             */
/*   Updated: 2023/06/14 19:31:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	cross(t_vec v1, t_vec v2)
{
	t_vec	ret;

	calc_outerproduct(&ret, &v1, &v2);
	return (ret);
}

t_vec	add(t_vec v1, t_vec v2)
{
	t_vec	ret;

	add_vec(&ret, &v1, &v2);
	return (ret);
}

t_vec	sub(t_vec v1, t_vec v2)
{
	t_vec	ret;

	neg_vec(&ret, &v1, &v2);
	return (ret);
}

double	dot(t_vec v1, t_vec v2)
{
	return (dot_vec(&v1, &v2));
}

// t_vec	norm_vec(t_vec v)
// {
// 	t_vec	ret;

// 	normalize(&ret, &v);
// 	return(ret);
// }

t_vec	vec_k1v1_k2v2(double k1, t_vec v1, double k2, t_vec v2)
{
	t_vec	ret;

	setvec(&ret, \
	k1 * v1.x + k2 * v2.x, \
	k1 * v1.y + k2 * v2.y, \
	k1 * v1.z + k2 * v2.z);
	return (ret);
}
