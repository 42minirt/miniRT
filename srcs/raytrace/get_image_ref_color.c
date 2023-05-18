#include "minirt.h"

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

	img_color = get_img_color(its_p);
	bump_normal_local.x = (img_color.r - 0.5) / 0.5;
	bump_normal_local.y = (img_color.g - 0.5) / 0.5;
	bump_normal_local.z = (img_color.b - 0.5) / 0.5;

	// its_p.normal = +v
	trans_mat = get_transform_matrix_world2local_yup(its_p->normal);
	bump_normal_world = mul_matrix_vec(trans_mat, bump_normal_local);
	bump_normal_world = norm_vec(bump_normal_world);
	return (bump_normal_world);
}

t_color	get_image_ref_color(t_diffuse_param p)
{
	t_color	ret_color;
	t_color	img_color;

	ret_color = init_color(0.0, 0.0, 0.0);
	if (!is_image_data_exists(p.its_p->obj->obj_color))
		return (ret_color);

	img_color = get_img_color(p.its_p);
	ret_color = color_k1c1_k2c2(1.0, img_color, \
								p.dot_n_pos2light, p.light->light_color);
	return (ret_color);
}
