#include "minirt.h"

t_vec	get_bump_normal(t_intersection_point *its_p)
{

}

t_vec	get_normal(t_intersection_point *its_p)
{
	if (is_bump_data_exists(its_p->obj->obj_color))
		return (get_bump_normal(its_p));
	return (its_p->normal);
}

t_color	get_image_color(t_diffuse_param p)
{

}