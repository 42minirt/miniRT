/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_vec_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:27:25 by user              #+#    #+#             */
/*   Updated: 2023/06/13 23:27:51 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	inverse(t_vec vec)
{
	t_vec	ret;

	inverse_vec(&ret, &vec);
	return (ret);
}

t_vec	inv_norm(t_vec vec)
{
	t_vec	ret;

	inverse_vec(&ret, &vec);
	ret = norm_vec(ret);
	return (ret);
}

t_vec	set(double x, double y, double z)
{
	t_vec	ret;

	setvec(&ret, x, y, z);
	return (ret);
}
