#include "minirt.h"

// todo: get_texture_coordinate_mapにまとまったので不要かも
//t_tangetnt_map	get_tangent_coordinate_map(t_intersection_point *its_p, t_img img)
//{
//	const t_shape_type	type = its_p->obj->type;
//	t_tangetnt_map		map;
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

static t_map_idx	get_map_idx(t_tangetnt_map map, t_img img)
{
	t_map_idx	ret;

	map.u *= (double)img.width * IMG_FREQUENCY;
	map.v *= -1.0 * (double)img.height * IMG_FREQUENCY;
	ret.row = ((int)map.u % img.width + img.width ) % img.width;
	ret.col = ((int)map.v % img.height + img.height ) % img.height;
	ret.idx = ((ret.col * img.width + ret.row) * PPM_RGB_UNIT) % (img.width * img.height * PPM_RGB_UNIT);
	return (ret);
}

t_color	get_its_pos_img_color(t_intersection_point *its_p, t_img img)
{
	t_color				ret_color;
	t_tangetnt_map		map;
	t_map_idx			i;

	map = get_tangent_coordinate_map(its_p, img);
	i = get_map_idx(map, img);
	ret_color.r = img.data[i.idx++];
	ret_color.g = img.data[i.idx++];
	ret_color.b = img.data[i.idx];
	return (ret_color);
}
