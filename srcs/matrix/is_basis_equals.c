/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_basis_equals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:03:10 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:14:50 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

bool	is_ev_equals_ey(t_basis_world world, t_basis_local local)
{
	return (local.ev.x == world.ey.x \
	&& local.ev.y == world.ey.y \
	&& local.ev.z == world.ey.z);
}

bool	is_ev_equals_inv_ey(t_basis_world world, t_basis_local local)
{
	return (local.ev.x == world.ey.x \
	&& local.ev.y == -1.0 * world.ey.y \
	&& local.ev.z == world.ey.z);
}

bool	is_ev_equals_ex(t_basis_world world, t_basis_local local)
{
	return (local.ev.x == world.ex.x \
	&& local.ev.y == world.ex.y \
	&& local.ev.z == world.ex.z);
}

bool	is_ev_equals_inv_ex(t_basis_world world, t_basis_local local)
{
	return (local.ev.x == -1.0 * world.ex.x \
	&& local.ev.y == world.ex.y \
	&& local.ev.z == world.ex.z);
}
