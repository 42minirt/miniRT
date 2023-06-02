/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_ref_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:08:09 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_map_idx	get_map_idx(t_tangetnt_map map, t_img img)
{
	t_map_idx	ret;

	map.u *= (double)img.width * IMG_FREQUENCY;
	map.v *= (double)img.height * IMG_FREQUENCY;
	ret.row \
	= ((int)map.u % (int)img.width + (int)img.width) % (int)img.width;
	ret.col \
	= ((int)map.v % (int)img.height + (int)img.height) % (int)img.height;
	ret.idx = ((ret.col * (int)img.width + ret.row) * PPM_RGB_UNIT) \
				% ((int)img.width * (int)img.height * PPM_RGB_UNIT);
	return (ret);
}

// img.data:[0.0, 255.0]
// color   :[0.0,   1.0]
static t_color	get_its_pos_img_color(t_intersection_point *its_p, t_img img)
{
	t_color				ret_color;
	t_tangetnt_map		map;
	t_map_idx			i;

	if (!img.data)
		return (init_color(0, 0, 0));
	map = get_tangent_coordinate_map(its_p);
	i = get_map_idx(map, img);
	ret_color.r = img.data[i.idx++] / 255.0;
	ret_color.g = img.data[i.idx++] / 255.0;
	ret_color.b = img.data[i.idx] / 255.0;
	return (ret_color);
}

t_color	get_itspos_image_texture_color(t_diffuse_param p)
{
	t_color	img_color;

	if (!is_obj_image_texture(p.its_p.obj->obj_color))
		return (init_color(0.0, 0.0, 0.0));
	img_color \
	= get_its_pos_img_color(&p.its_p, p.its_p.obj->obj_color.texture_data);
	return (img_color);
}

//   img.data:[ 0.0,  1.0]
//   normal  :[-1.0, +1.0]

// img(x,y,z) -> left(x,z,y)

// 物体表面の法線ベクトルを変更し、凹凸を表現
t_vec	get_bump_normal(t_intersection_point *its_p)
{
	t_color		img_color;
	t_vec		bump_normal_local;
	t_vec		bump_normal_world;
	t_matrix	trans_mat_world2local;
	t_matrix	trans_mat_local2world;

	if (!its_p->obj->obj_color.bump_data.data)
		return (its_p->normal);
	img_color = get_its_pos_img_color(its_p, its_p->obj->obj_color.bump_data);
//	bump_normal_local.x = img_color.r;
//	bump_normal_local.y = img_color.b;
//	bump_normal_local.z = img_color.g;
	bump_normal_local.x = (img_color.r - 0.5) / 0.5;
	bump_normal_local.y = (img_color.b - 0.5) / 0.5;
	bump_normal_local.z = (img_color.g - 0.5) / 0.5;
	trans_mat_world2local = get_transform_matrix_world2local_yup(its_p->normal);
	trans_mat_local2world = transpose_matrix(trans_mat_world2local);
	bump_normal_world \
	= mul_matrix_vec(trans_mat_local2world, bump_normal_local);
	bump_normal_world = norm_vec(bump_normal_world);
	return (bump_normal_world);
}
