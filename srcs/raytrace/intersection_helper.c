#include "minirt.h"

// t1 < t2
// if D == 0; t1 == t2
void	solve_quadratic_equation(t_d_param *d_param)
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

double	calc_discriminant(double a, double b, double c)
{
	return (pow(b, 2) - 4.0 * a * c);
}
