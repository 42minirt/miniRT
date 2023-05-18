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

static t_color	get_its_pos_img_color(t_intersection_point *its_p, t_img img)
{
	t_color				ret_color;
	t_tangetnt_map		map;
	t_map_idx			i;

	map = get_tangent_coordinate_map(its_p);
	i = get_map_idx(map, img);
	ret_color.r = img.data[i.idx++];
	ret_color.g = img.data[i.idx++];
	ret_color.b = img.data[i.idx];
	return (ret_color);
}

t_color	get_image_texture_ref_color(t_diffuse_param p)
{
	t_color	ret_color;
	t_color	img_color;

	ret_color = init_color(0.0, 0.0, 0.0);
	if (!is_image_data_exists(p.its_p->obj->obj_color))
		return (ret_color);

	img_color = get_its_pos_img_color(p.its_p,
									  p.its_p->obj->obj_color.texture_data);
	ret_color = color_k1c1_k2c2(1.0, img_color, \
								p.dot_n_pos2light, p.light->light_color);
	return (ret_color);
}

// img_color
//   ppm     :[0, 255]
//   img.data:[0, 1]
//   normal  :[-0.5, +0.5]

// 物体表面の法線ベクトルを変更し、凹凸を表現
t_vec	get_bump_normal(t_intersection_point *its_p)
{
	t_color		img_color;
	t_vec		bump_normal_local;
	t_vec		bump_normal_world;
	t_matrix	trans_mat;

	img_color = get_its_pos_img_color(its_p, its_p->obj->obj_color.bump_data);
	bump_normal_local.x = (img_color.r - 0.5) / 0.5;
	bump_normal_local.y = (img_color.g - 0.5) / 0.5;
	bump_normal_local.z = (img_color.b - 0.5) / 0.5;

	// its_p.normal = +v
	trans_mat = get_transform_matrix_world2local_yup(its_p->normal);
	bump_normal_world = mul_matrix_vec(trans_mat, bump_normal_local);
	bump_normal_world = norm_vec(bump_normal_world);
	return (bump_normal_world);
}
