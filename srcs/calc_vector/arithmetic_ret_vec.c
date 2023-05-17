#include "minirt.h"

t_vec	cross(t_vec v1, t_vec v2)
{
	t_vec	ret;
	calc_outerproduct(&ret, &v1, &v2);
	return(ret);
}

t_vec	add(t_vec v1, t_vec v2)
{
	t_vec	ret;
	add_vec(&ret, &v1, &v2);
	return(ret);
}

t_vec	sub(t_vec v1, t_vec v2)
{
	t_vec	ret;
	neg_vec(&ret, &v1, &v2);
	return(ret);
}

double	dot(t_vec v1, t_vec v2)
{
	return (dot_vec(&v1, &v2));
}

t_vec	norm_vec(t_vec v)
{
	t_vec	ret;
	normalize(&ret, &v);
	return(ret);
}

t_vec	vec_k1v1_k2ve(double k1, t_vec v1, double k2, t_vec v2)
{
	t_vec	ret;

	t_mix_vec_all(&ret, k1, &v1, k2, &v2);
	return(ret);
}