#include "minirt.h"

// todo: 不要かも
//t_texture_map	get_texture_coordinate_map(t_intersection_point *its_p, t_img img)
//{
//	const t_shape_type	type = its_p->obj->type;
//	t_texture_map		map;
//
//	if (type == PLANE)
//		map = get_planner_texture_coordinate(its_p, img);
//	else if (type == BALL)
//		map = get_spherical_texture_coordinate(its_p, img);
//	else if (type == CYLINDER)
//		map = get_cylindrical_texture_coordinate(its_p, img);
//	else
//		map = get_conical_texture_coordinate(its_p, img);
//	return (map);
//}

t_texture_map	get_texture_coordinate_map(t_intersection_point *its_p, t_img img)
{
	const t_shape_type	type = its_p->obj->type;
	t_texture_map		map;

	if (type == PLANE)
		map = get_planer_map(its_p);
	else if (type == BALL)
		map = get_spherical_map(its_p);
	else if (type == CYLINDER)
		map = get_cylindrical_map(its_p);
	else
		map = get_conical_map(its_p);
	map.u *= (double)img.width * IMG_FREQUENCY;
	map.v *= -1.0 * (double)img.height * IMG_FREQUENCY;
	return (map);
}

t_map_idx	get_map_idx(t_texture_map map, t_img img)
{
	t_map_idx	ret;

	ret.row = ((int)map.u % img.width + img.width ) % img.width;
	ret.col = ((int)map.v % img.height + img.height ) % img.height;
	ret.idx = ((ret.col * img.width + ret.row) * PPM_RGB_UNIT) % (img.width * img.height * PPM_RGB_UNIT);
	return (ret);
}

t_color	get_intpos_img_color(t_intersection_point *its_p, t_img img)
{
	t_color				ret_color;
	t_texture_map		map;
	t_map_idx			i;

	map = get_texture_coordinate_map(its_p, img);
	i = get_map_idx(map, img);
	ret_color.r = img.data[i.idx++];
	ret_color.g = img.data[i.idx++];
	ret_color.b = img.data[i.idx];
	return (ret_color);
}
