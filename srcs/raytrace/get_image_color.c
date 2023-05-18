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

	img_color = get_image_color(its_p);
	bump_normal_local.x = (img_color.r - 0.5) / 0.5;
	bump_normal_local.y = (img_color.g - 0.5) / 0.5;
	bump_normal_local.z = (img_color.b - 0.5) / 0.5;

	// its_p.normal = +v
	trans_mat = get_transform_matrix_world2local_yup(its_p->normal);
	bump_normal_world = mul_matrix_vec(trans_mat, bump_normal_local);
	bump_normal_world = norm_vec(bump_normal_world);
	return (bump_normal_world);
}

t_color	get_image_color(t_intersection_point *its_p)
{

}