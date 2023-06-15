/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/06/14 20:25:52 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "typedef.h"

// arithmetic
void	add_vec(t_vec *sub, t_vec *v1, t_vec *v2);
void	neg_vec(t_vec *sub, t_vec *v1, t_vec *v2);
double	dot_vec(t_vec *v1, t_vec *v2);
void	calc_outerproduct(t_vec *tgt_vec, t_vec *v1, t_vec *v2);

// arithmetic_ret_vec
t_vec	cross(t_vec v1, t_vec v2);
t_vec	sub(t_vec v1, t_vec v2); // v1 - v2
t_vec	add(t_vec v1, t_vec v2); // v1 + v2
double	dot(t_vec v1, t_vec v2);
t_vec	norm_vec(t_vec vec);
t_vec	vec_k1v1_k2v2(double k1, t_vec v1, double k2, t_vec v2);

// calc
void	normalize(t_vec *normal_vec, t_vec *normarized_vec);
void	vector_scalar_product(t_vec *tgt_vec, double k, t_vec *v);
t_vec	k_vec(double k, t_vec v); // k*vec
double	norm(t_vec vec);

// organize_vec
void	setvec(t_vec *tgt_vec, double x, double y, double z);
t_vec	set(double x, double y, double z);

void	inverse_vec(t_vec *inv_vec, t_vec *inved_vec);
t_vec	inverse(t_vec vec);
t_vec	inv_norm(t_vec vec);
void	times_vec(t_vec *tgt_vec, double t, t_vec *sub);
double	obtain_vecsize(t_vec *vec);

#endif //VECTOR_H