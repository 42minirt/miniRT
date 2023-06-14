/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:20:24 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:14:40 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/* **********************

   +y                +v
   |  +z             |  +w
   | /               | /
   |/_____ +x        |/_____ +u

 world(x,y,z)       local(u,v,w)

 ********************** */

static void	set_world_basis_vec(t_basis_world *world)
{
	world->ex = set(1.0, 0.0, 0.0);
	world->ey = set(0.0, 1.0, 0.0);
	world->ez = set(0.0, 0.0, 1.0);
}

static t_matrix	set_vec_to_matrix(t_basis_local local)
{
	t_matrix	ret;

	ret.m11 = local.eu.x;
	ret.m12 = local.eu.y;
	ret.m13 = local.eu.z;
	ret.m21 = local.ev.x;
	ret.m22 = local.ev.y;
	ret.m23 = local.ev.z;
	ret.m31 = local.ew.x;
	ret.m32 = local.ew.y;
	ret.m33 = local.ew.z;
	return (ret);
}

// convert basis vector of point (x,y,z)->(u,v,w)
// set v_dir = -d by caller

// sphere, camera
t_matrix	get_trans_mat_world2local_yup(t_vec v_dir)
{
	t_basis_world	world;
	t_basis_local	local;
	t_matrix		transform_mat_w2l;

	set_world_basis_vec(&world);
	local.ev = norm_vec(v_dir);
	local.eu = cross(local.ev, world.ey);
	local.ew = cross(local.eu, local.ev);
	if (is_ev_equals_ey(world, local))
	{
		local.eu = world.ex;
		local.ew = world.ez;
	}
	else if (is_ev_equals_inv_ey(world, local))
	{
		local.eu = world.ex;
		local.ew = inverse(world.ez);
	}
	transform_mat_w2l = set_vec_to_matrix(local);
	return (transform_mat_w2l);
}
//	transform_mat_w2l = transpose_matrix(transform_mat_w2l);

t_matrix	get_trans_mat_world2local_zup(t_vec w_dir)
{
	t_basis_world	world;
	t_basis_local	local;
	t_matrix		transform_mat_w2l;

	set_world_basis_vec(&world);
	local.ev = norm_vec(w_dir);
	local.eu = cross(local.ev, world.ez);
	local.ew = cross(local.eu, local.ev);
	if (is_ev_equals_ez(world, local))
	{
		local.eu = inverse(world.ex);
		local.ew = world.ey;
	}
	else if (is_ev_equals_inv_ez(world, local))
	{
		local.eu = world.ex;
		local.ew = world.ey;
	}
	transform_mat_w2l = set_vec_to_matrix(local);
	return (transform_mat_w2l);
}
//	transform_mat_w2l = transpose_matrix(transform_mat_w2l);
