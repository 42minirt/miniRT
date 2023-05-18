/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_diffuse_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:39:36 by takira            #+#    #+#             */
/*   Updated: 2023/05/18 19:44:06 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	get_checker_ref_color(t_diffuse_param p)
{
	t_tangetnt_map	map;
	int				pattern_a;

	map = get_tangent_coordinate_map(p.its_p);
	pattern_a = (int)(floor(map.u * CHECKER_U_MAG) + floor(map.v * CHECKER_V_MAG)) % 2;
	if (pattern_a)
		return (p.its_p->obj->obj_color.checker_color);
	return (p.its_p->obj->obj_color.kd);
}

static bool	is_in_range_spotlight(t_diffuse_param p)
{
	double	angle_pos2light;

	angle_pos2light = acos(dot(p.vec_light2pos, \
							p.light->sl_dir)) * 180.0 / (2.0 * M_PI);
	if (angle_pos2light < 0)
		angle_pos2light *= -1.0; //todo: check
	return (angle_pos2light <= p.light->sl_angle);
}

static t_color	get_diffuse_ref_color(t_diffuse_param p)
{
	t_color	ret_color;

	ret_color = init_color(0.0, 0.0, 0.0);
	if (is_image_data_exists(p.its_p->obj->obj_color))
		return (ret_color);
	if (p.dot_n_pos2light <= 0.0)
		return (ret_color);
	if (p.light->type == LT_POINT && !is_in_range_spotlight(p))
		return (ret_color);
	ret_color = color_k1c1_k2c2(1.0, p.its_p->obj->obj_color.kd, \
							p.dot_n_pos2light, p.light->light_color);
	return (ret_color);
}

static t_color	calc_diffuse_ref_by_light(t_scene_info *scene, \
								t_intersection_point *its_p, \
								t_ray eye2screen, t_light *light)
{
	t_color			ret_color;
	t_diffuse_param	p;

	calc_diffuse_param(&p, its_p, eye2screen, light);
	ret_color = init_color(0.0, 0.0, 0.0);
	if (is_obj_exists_extension_of_ray(scene, p))
		return (ret_color);
	ret_color = color_add(ret_color, get_diffuse_ref_color(p));
	ret_color = color_add(ret_color, get_checker_ref_color(p));
	ret_color = color_add(ret_color, get_image_texture_ref_color(p));
	return (ret_color);
}

t_color	calc_diffuse_reflection(t_scene_info *scene, \
							t_intersection_point *its_p, t_ray eye2screen)
{
	t_color	ret_color;
	t_list	*node;
	t_light	*light;

	ret_color = init_color(0.0, 0.0, 0.0);
	if (is_obj_perfect_ref(its_p))
		return (ret_color);
	node = scene->lights;
	while (node)
	{
		light = node->content;
		ret_color = color_add(ret_color, \
		calc_diffuse_ref_by_light(scene, its_p, eye2screen, light));
		node = node->next;
	}
	return (ret_color);
}
