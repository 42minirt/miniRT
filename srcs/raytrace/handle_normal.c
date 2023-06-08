#include "minirt.h"

static bool	is_same_dir_pos2eye_and_pos2light(\
t_vec original_normal, t_ray ray, t_vec unit_pos2light)
{
	if (dot(original_normal, inverse(ray.unit_dir))\
	* dot(original_normal, unit_pos2light) <= 0)
		return (false);
	return (true);
}

double	calc_dot_n_l(t_intersection_point itsp, t_ray ray, t_vec unit_pos2light)
{
	const t_vec	original_normal = itsp.normal;
	t_vec		normal_to_calc;
	double		dot_normal_pos2light;

	normal_to_calc = get_normal(&itsp); // get bump or original normal
	dot_normal_pos2light = dot(normal_to_calc, unit_pos2light);
	if (dot_normal_pos2light <= 0 \
	|| !is_same_dir_pos2eye_and_pos2light(original_normal, ray, unit_pos2light))
		return (-1.0);
	return (dot_normal_pos2light);
}

t_vec	get_pl_sp_drawable_normal(t_intersection_point itsp, t_vec ray_dir)
{
	if (!is_equal_strings(itsp.obj->id_str, ID_PLANE)
	&& !is_equal_strings(itsp.obj->id_str, ID_SPHERE))
		return (itsp.normal);
	if (dot(itsp.normal, inverse(ray_dir)) >= 0)
		return (itsp.normal);
	return (inverse(itsp.normal));
}
