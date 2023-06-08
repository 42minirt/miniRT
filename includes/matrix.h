/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:18:34 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:15:06 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "minirt.h"

struct s_matrix
{
	double	m11;
	double	m12;
	double	m13;
	double	m21;
	double	m22;
	double	m23;
	double	m31;
	double	m32;
	double	m33;
};

struct s_basis_vec_world
{
	t_vec	ex;
	t_vec	ey;
	t_vec	ez;
};

struct s_basis_vec_local
{
	t_vec	eu;
	t_vec	ev;
	t_vec	ew;
};

t_matrix	get_transform_matrix_world2local_yup(t_vec v_dir);
t_matrix	get_trans_mat_world2local_zup(t_vec w_dir);

t_vec		mul_matrix_vec(t_matrix Matrix, t_vec vec);
t_matrix	transpose_matrix(t_matrix mat);

bool		is_ev_equals_ey(t_basis_world world, t_basis_local local);
bool		is_ev_equals_inv_ey(t_basis_world world, t_basis_local local);
bool		is_ev_equals_ez(t_basis_world world, t_basis_local local);
bool		is_ev_equals_inv_ez(t_basis_world world, t_basis_local local);

#endif //MATRIX_H
