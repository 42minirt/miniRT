#include "minirt.h"

// img_color
//   ppm     :[0, 255]
//   img.data:[0, 1]
//   normal  :[-0.5, +0.5]
static t_vec	get_bump_normal(t_intersection_point *its_p)
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

static t_vec	get_normal(t_intersection_point *its_p)
{
	if (is_bump_data_exists(its_p->obj->obj_color))
		return (get_bump_normal(its_p));
	return (its_p->normal);
}

void	calc_diffuse_param(t_diffuse_param *p, \
								t_intersection_point *its_p, \
								t_ray ray, t_light *light)
{
	p->ray = ray;
	p->vec_normal = get_normal(its_p);
	p->vec_pos2light = sub(light->point, its_p->position);
	p->vec_pos2light = norm_vec(p->vec_pos2light);
	p->vec_light2pos = inverse(p->vec_pos2light);
	p->vec_specular = norm_vec(p->vec_light2pos);

	p->dot_n_pos2light = dot(its_p->normal, p->vec_pos2light);
}
