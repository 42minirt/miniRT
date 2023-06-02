#include "minirt.h"

t_vec	get_pl_drawable_normal(t_intersection_point itsp, t_vec ray_dir)
{
	if (!is_equal_strings(itsp.obj->id_str, ID_PLANE))
		return (itsp.normal);
	if (dot(itsp.normal, inverse(ray_dir)) >= 0)
		return (itsp.normal);
	return (inverse(itsp.normal));
}
