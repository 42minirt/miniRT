/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:45:22 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:29:57 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	transpose_matrix(t_matrix mat)
{
	t_matrix	ret;

	ret.m11 = mat.m11;
	ret.m12 = mat.m21;
	ret.m13 = mat.m31;
	ret.m21 = mat.m12;
	ret.m22 = mat.m22;
	ret.m23 = mat.m32;
	ret.m31 = mat.m13;
	ret.m32 = mat.m23;
	ret.m33 = mat.m33;
	return (ret);
}

t_vec	mul_matrix_vec(t_matrix mat, t_vec vec)
{
	t_vec	ret;

	ret.x = mat.m11 * vec.x + mat.m12 * vec.y + mat.m13 * vec.z;
	ret.y = mat.m21 * vec.x + mat.m22 * vec.y + mat.m23 * vec.z;
	ret.z = mat.m31 * vec.x + mat.m32 * vec.y + mat.m33 * vec.z;
	return (ret);
}
