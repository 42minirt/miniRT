#ifndef MATRIX_H
# define MATRIX_H

# include "minirt.h"

struct s_matrix	//todo:norm
{
	double	m11, m12, m13;
	double	m21, m22, m23;
	double	m31, m32, m33;
};

/* **********************

   +y                +v
   |  +z             |  +w
   | /               | /
   |/_____ +x        |/_____ +u

 world(x,y,z)       local(u,v,w)

 ********************** */

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

t_vec		mul_matrix_vec(t_matrix Matrix, t_vec vec);
t_matrix	transpose_matrix(t_matrix mat);

bool		is_ev_equals_ey(t_basis_world world, t_basis_local local);
bool		is_ev_equals_inv_ey(t_basis_world world, t_basis_local local);
bool		is_ew_equals_ez(t_basis_world world, t_basis_local local);
bool		is_ew_equals_inv_ez(t_basis_world world, t_basis_local local);

#endif //MATRIX_H