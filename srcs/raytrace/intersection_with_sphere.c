#include "minirt.h"

static t_d_param	calc_discriminant_of_sphere(t_sphere *sphere, t_ray ray)
{
	t_vec		pe_pc;
	t_d_param	d_param;

	neg_vec(&pe_pc, &ray.pos, &sphere->center);
	d_param.a = dot_vec(&ray.unit_dir, &ray.unit_dir);
	d_param.b = 2.0 * dot_vec(&ray.unit_dir, &pe_pc);
	d_param.c = dot_vec(&pe_pc, &pe_pc) - sphere->radius * sphere->radius;
	d_param.d = d_param.b * d_param.b - 4.0 * d_param.a * d_param.c;
	return (d_param);
}

static double	get_t_of_sphere(double a, double b, double d)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(d)) / (2.0 * a);
	t2 = (-b + sqrt(d)) / (2.0 * a);

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

bool	is_intersect_with_sphere(t_shape_data *shape, t_ray ray, t_intersection_point *intp)
{
	t_sphere	*sphere;
	t_d_param	d_param;
	double		t;

	sphere = &shape->sphere;
	d_param = calc_discriminant_of_sphere(sphere, ray);
	if (d_param.a == 0.0 || d_param.d < 0.0)
		return (false);
	t = get_t_of_sphere(d_param.a, d_param.b, d_param.d);
	if (t <= 0.0 || !intp)
		return (false);
	*intp = calc_intp_info(sphere, ray, t);
	return (true);
}
