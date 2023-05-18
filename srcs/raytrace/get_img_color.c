#include "minirt.h"

static t_color	get_img_color_on_plane(t_intersection_point *its_p)
{
	t_color	ret_color;

	ret_color = init_color(0.0, 0.0, 0.0);

	return (ret_color);
}

static t_color	get_img_color_on_sphere(t_intersection_point *its_p)
{
	t_color	ret_color;

	ret_color = init_color(0.0, 0.0, 0.0);

	return (ret_color);
}

static t_color	get_img_color_on_cylinder(t_intersection_point *its_p)
{
	t_color	ret_color;

	ret_color = init_color(0.0, 0.0, 0.0);

	return (ret_color);
}

static t_color	get_img_color_on_corn(t_intersection_point *its_p)
{
	t_color	ret_color;

	ret_color = init_color(0.0, 0.0, 0.0);

	return (ret_color);
}


t_color	get_img_color(t_intersection_point *its_p)
{
	const t_shape_type	type = its_p->obj->type;
	t_color				ret_color;

	if (type == PLANE)
		return (get_img_color_on_plane(its_p));
	else if (type == BALL)
		return (get_img_color_on_sphere(its_p));
	else if (type == CYLINDER)
		return (get_img_color_on_cylinder(its_p));
	else if (type == CORN)
		return (get_img_color_on_corn(its_p));
	ret_color = init_color(0.0, 0.0, 0.0);
	return (ret_color);
}
