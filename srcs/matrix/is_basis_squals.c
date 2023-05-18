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

bool	is_ew_equals_ez(t_basis_world world, t_basis_local local)
{
	return (local.ew.x == world.ez.x \
	&& local.ew.y == world.ez.y \
	&& local.ew.z == world.ez.z);
}

bool	is_ew_equals_inv_ez(t_basis_world world, t_basis_local local)
{
	return (local.ew.x == world.ez.x \
	&& local.ew.y == world.ez.y \
	&& local.ew.z == -1.0 * world.ez.z);
}