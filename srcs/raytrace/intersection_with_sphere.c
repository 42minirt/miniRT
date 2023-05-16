#include "minirt.h"

static t_d_param	calc_discriminant_of_sphere(t_sphere *sphere, t_ray ray)
{
	t_vec		pe_pc;
	t_d_param	d_param;

	neg_vec(&pe_pc, &ray.pos, &sphere->center);
	d_param.a = dot_vec(&ray.unit_dir, &ray.unit_dir);
	d_param.b = 2.0 * dot_vec(&ray.unit_dir, &pe_pc);
	d_param.c = dot_vec(&pe_pc, &pe_pc) - pow(sphere->radius, 2);
	d_param.d = pow(d_param.b, 2) - 4.0 * d_param.a * d_param.c;
	return (d_param);
}

// t1 < t2
// if D == 0; t1 == t2
void	calc_t(t_d_param *d_param)
{
	const double	a = d_param->a;
	const double	b = d_param->b;
	const double	d = d_param->d;
	double			t1;
	double			t2;

	t1 = (-b - sqrt(d)) / (2.0 * a);
	t2 = (-b + sqrt(d)) / (2.0 * a);
	d_param->t1 = t1;
	d_param->t2 = t2;
}

double	get_valid_distance(double t1, double t2)
{
	if (t1 > 0.0)
		return (t1);
	if (t1 <= 0.0 && 0.0 < t2)
		return (t2);
	return (-1.0);
}

static t_intersection_point	calc_intp_info(t_sphere *sphere, t_ray ray, double t)
{
	t_intersection_point	intp;
	t_vec					td;

	intp.distance = t;
	vector_scalar_product(&td, t, &ray.unit_dir);
	add_vec(&intp.position, &ray.pos, &sphere->center);
	neg_vec(&intp.normal, &intp.position, &sphere->center);
	normalize(&intp.normal, &intp.normal);
	return (intp);
}

double	calc_intersect_with_sphere(t_sphere *sphere, t_ray ray, t_intersection_point *intp)
{
	t_d_param	d_param;
	double		t;

	d_param = calc_discriminant_of_sphere(sphere, ray);
	if (d_param.a == 0.0 || d_param.d < 0.0)
		return (-1.0);
	calc_t(&d_param);
	t = get_valid_distance(d_param.t1, d_param.t2);
	if (t <= 0.0 || !intp)
		return (-1.0);
	*intp = calc_intp_info(sphere, ray, t);
	return (intp->distance);
}
