#include "minirt.h"

#include "minirt.h"

static t_d_param	calc_d_param_of_corn(t_corn *corn, t_ray ray)
{
	t_d_param	d_param;

	d_param.d = pow(d_param.b, 2) - 4.0 * d_param.a * d_param.c;
	return (d_param);
}

static t_intersection_point	calc_intp_info_of_corn(t_corn *corn, t_ray ray, double t)
{
	t_intersection_point	intp;
	t_vec					td;

	intp.distance = t;
	return (intp);
}

double	calc_intersect_with_sphere(t_corn *corn, t_ray ray, t_intersection_point *intp)
{
	t_d_param	d_param;
	double		t;

	d_param = calc_d_param_of_corn(corn, ray);
	d_param.d = calc_discriminant(d_param.a, d_param.b, d_param.c);
	if (d_param.a == 0.0 || d_param.d < 0.0)
		return (-1.0);
	solve_quadratic_equation(&d_param);
	t = get_valid_distance(d_param.t1, d_param.t2);
	if (t <= 0.0 || !intp)
		return (-1.0);
	*intp = calc_intp_info_of_corn(corn, ray, t);
	return (intp->distance);
}
